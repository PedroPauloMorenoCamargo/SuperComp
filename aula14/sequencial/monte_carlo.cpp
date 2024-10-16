#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    const int N = 100000;  // Número de pontos aleatórios
    int points_in_circle = 0;
    double x, y;
    
    // Inicializa o gerador de números aleatórios com o tempo atual
    std::srand(std::time(0));
    
    // Começa a contar o tempo de execução
    clock_t start = clock();
    
    // Gera N pontos aleatórios e verifica quantos caem dentro do círculo
    for (int i = 0; i < N; ++i) {
        x = static_cast<double>(std::rand()) / RAND_MAX * 2.0 - 1.0;  // Gera um número entre -1 e 1
        y = static_cast<double>(std::rand()) / RAND_MAX * 2.0 - 1.0;  // Gera um número entre -1 e 1
        
        if (x * x + y * y <= 1.0) {
            points_in_circle++;
        }
    }
    
    // Estima o valor de pi
    double pi_estimate = 4.0 * points_in_circle / N;
    
    // Calcula o tempo de execução
    clock_t end = clock();
    double execution_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    // Exibe os resultados
    std::cout << "Valor estimado de Pi: " << pi_estimate << std::endl;
    std::cout << "Tempo de execução: " << execution_time << " segundos" << std::endl;
    
    return 0;
}
