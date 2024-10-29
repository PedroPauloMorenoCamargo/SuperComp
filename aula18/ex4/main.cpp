#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <cmath>

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
    double localMean = localSum / localSize;

    double localVariance = 0.0;
    for (int i = 0; i < localSize; ++i) {
        localVariance += (localData[i] - localMean) * (localData[i] - localMean);
    }
    localVariance /= localSize;

    std::cout << "Processo " << rank << " - Média local: " << localMean << ", Variância local: " << localVariance << std::endl;

    std::vector<double> localMeans(size);
    std::vector<double> localVariances(size);
    MPI_Gather(&localMean, 1, MPI_DOUBLE, localMeans.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&localVariance, 1, MPI_DOUBLE, localVariances.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double globalMean = std::accumulate(localMeans.begin(), localMeans.end(), 0.0) / size;
        std::cout << "Médias locais coletadas: ";
        for (double mean : localMeans) {
            std::cout << mean << " ";
        }
        std::cout << "\nMédia global: " << globalMean << std::endl;

        double globalVariance = 0.0;
        for (int i = 0; i < size; ++i) {
            globalVariance += localVariances[i] + (localMeans[i] - globalMean) * (localMeans[i] - globalMean);
        }
        globalVariance /= size;
        std::cout << "Variâncias locais coletadas: ";
        for (double variance : localVariances) {
            std::cout << variance << " ";
        }
        std::cout << "\nVariância global: " << globalVariance << std::endl;

        double globalStdDev = std::sqrt(globalVariance);
        std::cout << "Desvio padrão global do array: " << globalStdDev << std::endl;
    }

    MPI_Finalize();
    return 0;
}
