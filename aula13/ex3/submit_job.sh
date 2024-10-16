#!/bin/bash
#SBATCH --job-name=vector_mem
#SBATCH --output=vector_mem.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1024
#SBATCH --time=00:05:00

./vector_mem