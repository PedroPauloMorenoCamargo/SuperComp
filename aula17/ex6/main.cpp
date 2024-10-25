#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            std::string mensagem = "Mensagem para o processo " + std::to_string(i);
            MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo " << rank << " enviou mensagem para o processo " << i << std::endl;

            char resposta[50];
            MPI_Recv(resposta, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Processo " << rank << " recebeu resposta do processo " << i << std::endl;
        }
    } else {
        char mensagem[50];
        MPI_Recv(mensagem, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: mensagem do processo 0" << std::endl;

        std::string resposta = "Resposta do processo " + std::to_string(rank);
        MPI_Send(resposta.c_str(), resposta.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou resposta para o processo 0" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
