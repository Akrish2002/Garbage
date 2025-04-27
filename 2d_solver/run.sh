#!/bin/bash
#SBATCH -JAbhi
#SBATCH -N1 --ntasks-per-node=1
#SBATCH --mem-per-cpu=180G
#SBATCH -t10:00:00
#SBATCH -oAbhi.out

./cfd_test


