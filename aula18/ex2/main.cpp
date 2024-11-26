#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numIterations = 0;

    if (rank == 0) {
        numIterations = 1000000;
        std::cout << "Processo raiz definindo número de iterações: " << numIterations << std::endl;
    }

    MPI_Bcast(&numIterations, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double localResult = 0.0;
    for (int i = 0; i < numIterations; ++i) {
        localResult += std::sin(i * 0.001);
    }

    std::cout << "Processo " << rank << " - Resultado local: " << localResult << std::endl;

    MPI_Finalize();
    return 0;
}
