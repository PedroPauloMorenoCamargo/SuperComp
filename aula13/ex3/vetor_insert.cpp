#include <vector>
#include <iostream>
#include <omp.h>

// Função de cálculo complexa (apenas um exemplo)
double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 100000; 
    std::vector<double> vec;

    // Medir o tempo de execução
    double start_time = omp_get_wtime();

    // Paralelizar a criação do vetor com OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double resultado = conta_complexa(i);

        // Região crítica para evitar acessos simultâneos ao vetor
        #pragma omp critical
        {
            vec.push_back(resultado);
        }
    }

    // Medir o tempo final
    double end_time = omp_get_wtime();

    // Imprimir o tempo de execução
    std::cout << "Tempo de execucao: " << end_time - start_time << " segundos" << std::endl;


    return 0;
}
