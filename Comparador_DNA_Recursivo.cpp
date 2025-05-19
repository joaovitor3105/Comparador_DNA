#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int calcularComprimentoSubcadeia(const std::vector<std::string> &codons,
                                 const std::vector<std::string> &codonsEntrada,
                                 int i, int j)
{
    if (i >= codons.size() || j >= codonsEntrada.size())
    {
        return 0;
    }

    if (codons[i] == codonsEntrada[j])
    {
        return 1 + calcularComprimentoSubcadeia(codons, codonsEntrada, i + 1, j + 1);
    }

    return 0;
}

std::pair<int, int> encontrarIndicesMaiorSubcadeiaRecursiva(
    const std::vector<std::string> &codons,
    const std::string &entrada)
{

    std::vector<std::string> codonsEntrada = dividirEmCodons(entrada);

    int maxLen = 0;
    int inicioMaximo = 0;
    int fimMaximo = -1;

    for (int i = 0; i < codons.size(); ++i)
    {
        for (int j = 0; j < codonsEntrada.size(); ++j)
        {
            int comprimento = calcularComprimentoSubcadeia(codons, codonsEntrada, i, j);

            if (comprimento > maxLen)
            {
                maxLen = comprimento;
                inicioMaximo = i;
                fimMaximo = i + comprimento - 1;
            }
        }
    }

    return std::make_pair(inicioMaximo, fimMaximo);
}
std::vector<std::string> dividirEmCodons(const std::string &sequencia)
{
    std::vector<std::string> codons;

    for (size_t i = 0; i + 2 < sequencia.length(); i += 3)
    {
        codons.push_back(sequencia.substr(i, 3));
    }

    return codons;
}

int main()
{
    std::string sequenciaDNA;

    std::cout << "Digite o nome do arquivo com a sequência de DNA: ";
    std::string nomeArquivo;
    std::cin >> nomeArquivo;

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo)
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::getline(arquivo, sequenciaDNA);
    arquivo.close();

    std::vector<std::string> codons = dividirEmCodons(sequenciaDNA);

    std::cout << "Digite a sequência de DNA para comparação: ";
    std::string entrada;
    std::cin >> entrada;

    auto indices = encontrarIndicesMaiorSubcadeiaRecursiva(codons, entrada);

    if (indices.second != -1)
    {
        std::cout << "Maior subcadeia contígua encontrada entre os índices "
                  << indices.first << " e " << indices.second << "." << std::endl;
        std::cout << "Subcadeia: ";
        for (int i = indices.first; i <= indices.second; ++i)
        {
            std::cout << codons[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Nenhuma subcadeia contígua encontrada." << std::endl;
    }

    return 0;
}
