#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        std::string mensagem = "Olá";
        MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        char resposta[3];
        MPI_Recv(resposta, 3, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << resposta<<std::endl;

    } else if (rank == 1) {

        char mensagem[5];
        MPI_Recv(mensagem, 5, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << mensagem<<std::endl;

        std::string resposta = "Oi";
        MPI_Send(resposta.c_str(), resposta.size() + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
