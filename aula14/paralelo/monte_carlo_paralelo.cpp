#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>

int main() {
    const int N = 100000;  // Número de pontos aleatórios
    int points_in_circle = 0;
    double x, y;

    // Inicializa o gerador de números aleatórios com o tempo atual
    std::srand(std::time(0));

    // Começa a contar o tempo de execução
    double start_time = omp_get_wtime();

    // Paraleliza o sorteio de pontos e usa a redução para somar os pontos dentro do círculo
    #pragma omp parallel for private(x, y) reduction(+:points_in_circle)
    for (int i = 0; i < N; ++i) {
        // Gera números aleatórios entre -1 e 1
        x = static_cast<double>(std::rand()) / RAND_MAX * 2.0 - 1.0;
        y = static_cast<double>(std::rand()) / RAND_MAX * 2.0 - 1.0;

        // Verifica se o ponto está dentro do círculo
        if (x * x + y * y <= 1.0) {
            points_in_circle++;
        }
    }

    // Estima o valor de pi
    double pi_estimate = 4.0 * points_in_circle / N;

    // Calcula o tempo de execução
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Exibe os resultados
    std::cout << "Pi: " << pi_estimate << " , " << execution_time << " s" << std::endl;

    return 0;
}
