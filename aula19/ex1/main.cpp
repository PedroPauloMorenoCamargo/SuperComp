#include <iostream>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 10;
    int data[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                data[i][j] = i + j;
            }
        }
    }

    int chunk_size = N / size;
    int local_data[chunk_size][N];
    MPI_Scatter(data, chunk_size * N, MPI_INT, local_data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    #pragma omp parallel for collapse(2) 
    for (int i = 0; i < chunk_size; i++) {
        for (int j = 0; j < N; j++) {
            local_data[i][j] *= local_data[i][j]; 
        }
    }

    MPI_Gather(local_data, chunk_size * N, MPI_INT, data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    
    if (rank == 0) {
        std::cout << "Tempo de execução: " << end_time - start_time << " segundos" << std::endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
