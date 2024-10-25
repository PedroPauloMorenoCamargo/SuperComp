#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Valor exclusivo para cada processo
    int valor = rank + 1;  // Por exemplo, cada processo usa seu rank + 1 como valor
    int soma;

    if (rank == 0) {
        // Processo 0 inicia a soma
        soma = valor;
        std::cout << "Processo " << rank << " inicia com valor: " << soma << std::endl;

        // Envia a soma para o próximo processo
        MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        // Recebe a soma do processo anterior
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Soma o valor do processo atual
        soma += valor;
        std::cout << "Processo " << rank << " recebeu soma parcial: " << soma - valor 
                  << " e adicionou seu valor " << valor << " para totalizar: " << soma << std::endl;

        if (rank < size - 1) {
            // Envia a nova soma para o próximo processo
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Último processo exibe a soma total
            std::cout << "Processo " << rank << " exibe a soma total: " << soma << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
