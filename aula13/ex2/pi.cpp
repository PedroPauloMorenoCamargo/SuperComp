#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l * 1024 * 1024 * 2;
#define MIN_BLK 1024 * 1024 * 1024 // Ajuste o valor de MIN_BLK para testar desempenho

void pi_r(long Nstart, long Nfinish, double step, double &local_sum) {
    long i;
    if (Nfinish - Nstart < MIN_BLK) {
        // Paralelizando o loop com omp parallel for
        #pragma omp parallel for reduction(+:local_sum)
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }
    } else {
        long iblk = (Nfinish - Nstart) / 2;
        pi_r(Nstart, Nstart + iblk, step, local_sum);
        pi_r(Nstart + iblk, Nfinish, step, local_sum);
    }
}

int main() {
    double step, pi = 0.0;
    double init_time, final_time;

    step = 1.0 / (double)num_steps;
    init_time = omp_get_wtime();

    #pragma omp parallel
    {
        double local_sum = 0.0; // Variável local para cada thread

        #pragma omp single
        {
            pi_r(0, num_steps, step, local_sum); // Iniciar a recursão
        }

        #pragma omp atomic
        pi += local_sum; // Somar o resultado local de forma segura à variável global pi
    }

    pi *= step;
    final_time = omp_get_wtime() - init_time;

    std::cout << "Para " << num_steps << " passos, pi = " << std::setprecision(15) << pi
              << " em " << final_time << " segundos\n";

    return 0;
}