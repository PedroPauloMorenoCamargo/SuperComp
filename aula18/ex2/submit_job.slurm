#!/bin/bash
#SBATCH --job-name=ex2
#SBATCH --output=ex2.txt
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=1
#SBATCH --mem=1024
#SBATCH --time=00:05:00
#SBATCH --partition=normal

mpirun ./main