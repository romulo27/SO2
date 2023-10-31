#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

int valorDeslocamento = 12; // Contagem do deslocamento
int tamanhoPagina = 1 << valorDeslocamento;
int mascaraDeDeslocamento = (1 << valorDeslocamento) - 1; // Tamanho do deslocamento pra operação 32

// Função para calcular a página e o deslocamento com base em um endereço
std::pair<int, int> getPaginaDeslocamento(int endereco) {
    int pagina = endereco >> valorDeslocamento;
    int deslocamento = endereco & (tamanhoPagina - 1);
    return std::make_pair(pagina, deslocamento);
}

int main(int argc, char* argv[]) {
    // Aviso para usar a linha de comando
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <endereco>" << std::endl;
        return 1;
    }
    
    // Realiza os devidos cálculos e obtém o valor da linha de comando
    int endereco = std::stoi(argv[1]);

    std::pair<int, int> deslocamentoPaginas = getPaginaDeslocamento(endereco);
    int pagina = deslocamentoPaginas.first;
    int deslocamento = deslocamentoPaginas.second;
    int enderecoFisico = (pagina * (1 << valorDeslocamento)) + deslocamento;

    // Lê o arquivo e converte os dados lidos em inteiros
    std::ifstream file("data_memory.txt");
    int valorPos = 0;
    for (int i = 0; i < enderecoFisico; ++i) {
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        iss >> valorPos;
    }
    file.close();
    std::cout << "Endereco fisico: " << enderecoFisico << std::endl;
    std::cout << "Deslocamento: " << deslocamento << std::endl;
    std::cout << "Valor lido: " << valorPos << std::endl;
    std::cout << "Pagina: " << pagina << std::endl;
    
    return 0;
}
