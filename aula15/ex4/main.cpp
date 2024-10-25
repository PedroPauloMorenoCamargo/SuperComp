#include <mpi.h>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Processo 0 envia mensagens exclusivas para cada processo
        for (int i = 1; i < size; ++i) {
            std::ostringstream oss;
            oss << "Segredo: " << i;
            std::string mensagem = oss.str();

            MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Demais processos recebem suas mensagens
        char buffer[50];
        MPI_Recv(buffer, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << buffer << std::endl;
    }

    MPI_Finalize();
    return 0;
}
