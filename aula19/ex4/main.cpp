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
    const int target = 42; 
    std::vector<int> data(N);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            data[i] = i % 100;
        }
    }

    int chunk_size = N / size;
    int remainder = N % size;

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

    std::vector<int> local_positions;

    #pragma omp parallel for
    for (int i = 0; i < local_chunk_size; i++) {
        if (local_data[i] == target) {
            #pragma omp critical
            local_positions.push_back(displs[rank] + i);
        }
    }

    int local_size = local_positions.size();
    std::vector<int> all_sizes(size);
    MPI_Gather(&local_size, 1, MPI_INT, all_sizes.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<int> global_positions;
    if (rank == 0) {
        int total_positions = 0;
        for (int s : all_sizes) {
            total_positions += s;
        }
        global_positions.resize(total_positions);
    }

    std::vector<int> displs_gather(size);
    if (rank == 0) {
        int offset = 0;
        for (int i = 0; i < size; i++) {
            displs_gather[i] = offset;
            offset += all_sizes[i];
        }
    }

    MPI_Gatherv(local_positions.data(), local_size, MPI_INT, global_positions.data(), all_sizes.data(), displs_gather.data(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Posições do valor " << target << " encontradas: ";
        for (int pos : global_positions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
