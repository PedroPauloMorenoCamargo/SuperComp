#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  

    if (size < 3) {
        if (rank == 0) {
            std::cerr << "O número de processos deve ser maior que 2." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    
    int mensagem = rank + 1; 

    if (rank == 0) {
        MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&mensagem, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu " << mensagem << " do processo " << size - 1 << std::endl;

    } else {
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu " << mensagem << " do processo " << rank - 1 << std::endl;

        int next_rank = (rank + 1) % size; 
        MPI_Send(&mensagem, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
