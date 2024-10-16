#!/bin/bash
#SBATCH --job-name=pi_tasks
#SBATCH --output=pi_tasks.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1024
#SBATCH --time=00:05:00

./pi_tasks