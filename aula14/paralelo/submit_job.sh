#!/bin/bash
#SBATCH --job-name=monte_carlo_paralelo
#SBATCH --output=monte_carlo_paralelo.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1024
#SBATCH --time=00:05:00

./monte_carlo_paralelo