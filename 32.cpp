// Esse código possui altas quantias de ctrl c ctrl v do anterior.
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

int valorDeslocamento = 12;
int tamanhoPagina = 10;
int mascaraDeslocamento = (1 << valorDeslocamento) - 1;

std::tuple<int, int, int> getPaginaDeslocamento(int endereco) {
    int paginaA = endereco >> (valorDeslocamento + tamanhoPagina); // Desloca os bits do endereço para a direita
    int paginaB = (endereco >> valorDeslocamento) & 0b1111111111; // Aplica uma máscara para obter os bits da segunda página
    int deslocamento = endereco & mascaraDeslocamento; // Aplica uma máscara de bits para manter apenas os bits de deslocamento
    return std::make_tuple(paginaA, paginaB, deslocamento);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <endereco>" << std::endl;
        return 1;
    }

    int endereco = std::stoi(argv[1]); // Converte a string de entrada para um inteiro

    std::tuple<int, int, int> deslocamentoPaginas = getPaginaDeslocamento(endereco);
    int paginaA = std::get<0>(deslocamentoPaginas);
    int paginaB = std::get<1>(deslocamentoPaginas);
    int deslocamento = std::get<2>(deslocamentoPaginas);
    int enderecoFisico = (paginaA << (valorDeslocamento + tamanhoPagina)) + (paginaB << valorDeslocamento) + deslocamento;

    std::ifstream file("data_memory.txt");
    int valor_pos = 0; // Declaração da variável valor_pos
    for (int i = 0; i < enderecoFisico; ++i) {
        std::string line;
        std::getline(file, line);
        valor_pos = std::stoi(line); // Converte a linha diretamente para um inteiro
    }
    file.close();

    std::cout << "Endereco fisico: " << enderecoFisico << std::endl;
    std::cout << "Deslocamento:" << deslocamento << std::endl;
    std::cout << "Valor lido: " << valor_pos << std::endl;
    std::cout << "Primeira pagina: " << paginaA << std::endl;
    std::cout << "Segunda pagina: " << paginaB << std::endl;

    return 0;
}
