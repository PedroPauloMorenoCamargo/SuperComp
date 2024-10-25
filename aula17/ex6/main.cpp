#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        // Processo 0 alterna mensagens com cada processo de rank > 0
        for (int i = 1; i < size; ++i) {
            // Envia uma mensagem para o processo i
            std::string mensagem = "Mensagem para o processo " + std::to_string(i);
            MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo " << rank << " enviou mensagem para o processo " << i << std::endl;

            // Recebe a resposta do processo i
            char resposta[50];
            MPI_Recv(resposta, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Processo " << rank << " recebeu resposta do processo " << i << std::endl;
        }
    } else {
        // Demais processos recebem e respondem ao processo 0
        char mensagem[50];
        MPI_Recv(mensagem, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: mensagem do processo 0" << std::endl;

        // Envia a resposta de volta para o processo 0
        std::string resposta = "Resposta do processo " + std::to_string(rank);
        MPI_Send(resposta.c_str(), resposta.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou resposta para o processo 0" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
