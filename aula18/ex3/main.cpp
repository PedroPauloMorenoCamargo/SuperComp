#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <omp.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 100; 
    int localSize = arraySize / size; 
    std::vector<int> data(arraySize);
    std::vector<int> localData(localSize);

    int maxVal = 0;


    if (rank == 0) {
        for (int i = 0; i < arraySize; ++i) {
            data[i] = rand() % 100; 
        }


        #pragma omp parallel for reduction(max: maxVal)
        for (int i = 0; i < arraySize; ++i) {
            maxVal = std::max(maxVal, data[i]);
        }

        std::cout << "Array inicializado pelo processo raiz: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\nValor máximo: " << maxVal << std::endl;
    }

    MPI_Bcast(&maxVal, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(data.data(), localSize, MPI_INT, localData.data(), localSize, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<double> localNormalized(localSize);
    for (int i = 0; i < localSize; ++i) {
        localNormalized[i] = static_cast<double>(localData[i]) / maxVal;
    }

    std::vector<double> normalizedData;
    if (rank == 0) {
        normalizedData.resize(arraySize);
    }
    MPI_Gather(localNormalized.data(), localSize, MPI_DOUBLE, normalizedData.data(), localSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Array normalizado: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << normalizedData[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
