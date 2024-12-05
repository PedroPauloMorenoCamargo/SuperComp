#!/bin/bash
#SBATCH --job-name=q1             # Nome do job
#SBATCH --output=q1.txt           # Arquivo para saída padrão
#SBATCH --ntasks=2                # Número de tarefas MPI (máquinas)
#SBATCH --cpus-per-task=5         # Número de CPUs (threads) por tarefa
#SBATCH --mem=3G                  # Memória total por nó
#SBATCH --time=00:05:00           # Tempo máximo de execução
#SBATCH --partition=prova         # Partição de execução

export OMP_NUM_THREADS=10         # Configurar número de threads OpenMP

mpirun ./executavel               # Executar o programa
