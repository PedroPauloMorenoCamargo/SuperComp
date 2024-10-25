#!/bin/bash
#SBATCH --job-name=ex6
#SBATCH --output=ex6.txt
#SBATCH --ntasks=6
#SBATCH --cpus-per-task=1
#SBATCH --mem=1024
#SBATCH --time=00:05:00
#SBATCH --partition=normal

mpirun ./main