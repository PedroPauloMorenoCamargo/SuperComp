#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int valor = rank + 1;  
    int soma;

    if (rank == 0) {
        soma = valor;
        std::cout << "Processo " << rank << " inicia com valor: " << soma << std::endl;

        MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        soma += valor;
        std::cout << "Processo " << rank << " recebeu soma parcial: " << soma - valor 
                  << " e adicionou seu valor " << valor << " para totalizar: " << soma << std::endl;

        if (rank < size - 1) {
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            std::cout << "Processo " << rank << " exibe a soma total: " << soma << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
