#include <iostream>   // Inclui a biblioteca padrão de entrada e saída, usada para operações como std::cout.
#include <chrono>     // Inclui a biblioteca para medição de tempo, usada para medir a performance do código.
#include <vector>
int main() {
    int N = 1000;  // Define o tamanho da matriz como N x N, onde N é 1000.

    auto inicio = std::chrono::high_resolution_clock::now();
    // Alocação dinâmica de memória para uma matriz N x N.
    // Primeiro, aloca um array de ponteiros, onde cada ponteiro irá apontar para uma linha da matriz.
    
    std::vector<std::vector<int>> matriz(N, std::vector<int>(N));

    int soma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;  // Preenche a matriz com a soma dos índices i e j
            soma += matriz[i][j];  // Calcula a soma total dos elementos
        }
    }

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();

    std::cout << "Soma: " << soma << std::endl;
    std::cout << "Tempo de execucaoo (alocacao dinamica manual): " << duracao << " ms" << std::endl;

    return 0;  // Retorna 0, indicando que o programa terminou com sucesso.
}