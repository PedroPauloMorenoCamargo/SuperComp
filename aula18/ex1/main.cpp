#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 100;
    int localSize = arraySize / size; 
    std::vector<int> data(arraySize);
    std::vector<int> localData(localSize);


    if (rank == 0) {
        for (int i = 0; i < arraySize; ++i) {
            data[i] = rand() % 100; 
        }
        std::cout << "Array inicializado pelo processo raiz: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }


    MPI_Scatter(data.data(), localSize, MPI_INT, localData.data(), localSize, MPI_INT, 0, MPI_COMM_WORLD);


    double localSum = std::accumulate(localData.begin(), localData.end(), 0);
    double localAverage = localSum / localSize;

    std::cout << "Processo " << rank << " - Média local: " << localAverage << std::endl;

    std::vector<double> localAverages(size);
    MPI_Gather(&localAverage, 1, MPI_DOUBLE, localAverages.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double globalSum = std::accumulate(localAverages.begin(), localAverages.end(), 0.0);
        double globalAverage = globalSum / size;
        std::cout << "Média global do array: " << globalAverage << std::endl;
    }

    MPI_Finalize();
    return 0;
}
