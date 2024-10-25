#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mensagem = 100;  // Mensagem inicial

    if (rank == 0) {
        // Processo 0 inicia a difusão
        MPI_Send(&mensagem, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou " << mensagem << " para o processo 1" << std::endl;
    } else {
        // Processos intermediários e o último recebem e reencaminham a mensagem
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu " << mensagem << " do processo " << rank - 1 << std::endl;

        if (rank < size - 1) {
            MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
