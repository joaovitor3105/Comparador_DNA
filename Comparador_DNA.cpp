#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> dividirEmCodons(const std::string &sequencia)
{
    std::vector<std::string> codons;

    for (size_t i = 0; i + 2 < sequencia.length(); i += 3)
    {
        codons.push_back(sequencia.substr(i, 3));
    }

    return codons;
}

std::pair<int, int> encontrarIndicesMaiorSubcadeia(const std::vector<std::string> &codons,
                                                   const std::string &entrada)
{
    std::vector<std::string> codonsEntrada = dividirEmCodons(entrada);
    int n = codons.size();
    int m = codonsEntrada.size();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    int maxLen = 0;
    int fimMaximo = -1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (codons[i] == codonsEntrada[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;

                if (dp[i + 1][j + 1] > maxLen)
                {
                    maxLen = dp[i + 1][j + 1];
                    fimMaximo = i;
                }
            }
            else
            {
                dp[i + 1][j + 1] = 0;
            }
        }
    }

    int inicioMaximo = fimMaximo - maxLen + 1;
    return std::make_pair(inicioMaximo, fimMaximo);
}

int main()
{
    std::string sequenciaDNA;

    std::cout << "Digite o nome do arquivo com a sequência de DNA: ";
    std::string nomeArquivo;
    std::cin >> nomeArquivo;

    std::ifstream arquivo(nomeArquivo);
    if (arquivo.is_open())
    {
        std::getline(arquivo, sequenciaDNA);
        arquivo.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo. Fornecendo entrada manualmente." << std::endl;
        std::cout << "Digite a sequência de DNA: ";
        std::cin >> sequenciaDNA;
    }

    std::string entradaExemplo = "ACGTGGCTCTCTAACGTACGTACGTACGGATGA";

    std::vector<std::string> codons = dividirEmCodons(sequenciaDNA);

    std::pair<int, int> indices = encontrarIndicesMaiorSubcadeia(codons, entradaExemplo);

    std::cout << "\nÍndices da maior cadeia:" << std::endl;
    std::cout << "Índice inicial: " << indices.first << std::endl;
    std::cout << "Índice final: " << indices.second << std::endl;
    std::cout << "Comprimento: " << (indices.second - indices.first + 1) << " códons(Triade de Nucleotídeos)" << std::endl;

    return 0;
}
