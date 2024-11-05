#include <iostream>
#include <mpi.h>
#include <omp.h>
#include <vector>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 1000;
    std::vector<int> data(N);
    int chunk_size = N / size;
    int remainder = N % size;

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            data[i] = i + 1; 
        }
    }

    int local_chunk_size = chunk_size + (rank < remainder ? 1 : 0);
    std::vector<int> local_data(local_chunk_size);

    std::vector<int> send_counts(size);
    std::vector<int> displs(size);
    int offset = 0;
    for (int i = 0; i < size; i++) {
        send_counts[i] = chunk_size + (i < remainder ? 1 : 0);
        displs[i] = offset;
        offset += send_counts[i];
    }

    MPI_Scatterv(data.data(), send_counts.data(), displs.data(), MPI_INT, local_data.data(), local_chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < local_chunk_size; i++) {
        local_sum += local_data[i];
    }

    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double mean = static_cast<double>(global_sum) / N;
        std::cout << "A média é: " << mean << std::endl;
    }

    MPI_Finalize();
    return 0;
}
