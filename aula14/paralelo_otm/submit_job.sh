#!/bin/bash
#SBATCH --job-name=paralelo_otm
#SBATCH --output=paralelo_otm.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1024
#SBATCH --time=00:05:00

./paralelo_otm