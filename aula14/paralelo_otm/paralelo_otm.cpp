#include <iostream>
#include <random>  // Para std::mt19937 e std::uniform_real_distribution
#include <omp.h>

int main() {
    const int N = 100000;  // Número de pontos aleatórios
    int points_in_circle = 0;

    // Começa a contar o tempo de execução
    double start_time = omp_get_wtime();

    // Paraleliza o sorteio de pontos e usa a redução para somar os pontos dentro do círculo
    #pragma omp parallel reduction(+:points_in_circle)
    {
        // Cada thread cria seu próprio gerador de números aleatórios
        std::random_device rd;  // Para gerar um seed único
        std::mt19937 gen(rd() ^ omp_get_thread_num());  // Gerador de números aleatórios por thread
        std::uniform_real_distribution<double> dist(-1.0, 1.0);  // Distribuição uniforme entre -1 e 1

        // Cada thread processa uma parte dos pontos
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            double x = dist(gen);  // Sorteia x entre -1 e 1
            double y = dist(gen);  // Sorteia y entre -1 e 1

            // Verifica se o ponto está dentro do círculo
            if (x * x + y * y <= 1.0) {
                points_in_circle++;
            }
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
