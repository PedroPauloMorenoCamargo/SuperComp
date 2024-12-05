#!/bin/bash
#SBATCH --job-name=fat
#SBATCH --output=fatorial1.txt
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=5
#SBATCH --mem=1024
#SBATCH --time=00:05:00
#SBATCH --partition=normal

mpirun ./fatorial