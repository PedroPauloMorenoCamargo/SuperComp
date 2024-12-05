#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int tag = 0; // Identificador da mensagem
    char message[10];

    if (rank == 0) {
        // Processo 0 envia "Olá" para o processo 1
        strcpy(message, "Olá");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
        printf("Processo 0 enviou: %s\n", message);

        // Processo 0 recebe resposta de "Oi" do processo 1
        MPI_Recv(message, 10, MPI_CHAR, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo 0 recebeu: %s\n", message);

    } else if (rank == 1) {
        // Processo 1 recebe "Olá" do processo 0
        MPI_Recv(message, 10, MPI_CHAR, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo 1 recebeu: %s\n", message);

        // Processo 1 envia "Oi" para o processo 0
        strcpy(message, "Oi");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
        printf("Processo 1 enviou: %s\n", message);
    }
    
    MPI_Finalize();
    return 0;
}
