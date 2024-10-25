#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtém o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtém o número total de processos

    if (size < 3) {
        if (rank == 0) {
            std::cerr << "O número de processos deve ser maior que 2." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Mensagem a ser enviada no anel
    int mensagem = rank + 1; 

    if (rank == 0) {
        // Processo com rank 0 envia para o próximo e espera o último fechar o anel
        MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&mensagem, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu " << mensagem << " do processo " << size - 1 << std::endl;

    } else {
        // Demais processos: recebe do processo anterior e envia para o próximo
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu " << mensagem << " do processo " << rank - 1 << std::endl;

        int next_rank = (rank + 1) % size;  // Próximo processo, ou 0 se for o último
        MPI_Send(&mensagem, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
