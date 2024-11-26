#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process setup
    std::vector<int> data;
    std::vector<int> sendCounts(size); // Number of elements for each process
    std::vector<int> displacements(size); // Start indices for each process

    if (rank == 0) {
        // Initialize the data array
        data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 

        // Define the number of elements to send to each process
        sendCounts = {3, 2, 4, 1}; // Assuming size = 4

        // Calculate displacements based on sendCounts
        displacements[0] = 0;
        for (int i = 1; i < size; i++) {
            displacements[i] = displacements[i - 1] + sendCounts[i - 1];
        }
    }

    // Each process needs a buffer to receive its chunk of data
    int recvCount = rank < size ? sendCounts[rank] : 0;
    std::vector<int> recvBuffer(recvCount);

    // Scatter the data
    MPI_Scatterv(data.data(), sendCounts.data(), displacements.data(), MPI_INT,
                 recvBuffer.data(), recvCount, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the data received by each process
    std::cout << "Process " << rank << " received:";
    for (int i : recvBuffer) {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
