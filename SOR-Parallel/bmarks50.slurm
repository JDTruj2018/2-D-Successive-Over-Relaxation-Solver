#!/bin/bash
#SBATCH --account=sc3260
#SBATCH --partition=mic
#SBATCH --reservation=sc3260
#SBATCH --time=02:00:00
#SBATCH --mem=4G
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --nodes=1

module load Intel/2016.3.210-GCC-5.4.0-2.26
module load icc/.2016.3.210-GCC-5.4.0-2.26  
make cleanall
make

export OMP_NUM_THREADS=1
time ./bin/run_SOR -Nx 50 -Ny 50 -iter 500000 > Results/Results50_1.txt

export OMP_NUM_THREADS=2
time ./bin/run_SOR -Nx 50 -Ny 50 -iter 500000 > Results/Results50_2.txt

export OMP_NUM_THREADS=4
time ./bin/run_SOR -Nx 50 -Ny 50 -iter 500000 > Results/Results50_4.txt

export OMP_NUM_THREADS=8
time ./bin/run_SOR -Nx 50 -Ny 50 -iter 500000 > Results/Results50_8.txt

export OMP_NUM_THREADS=16
time ./bin/run_SOR -Nx 50 -Ny 50 -iter 500000 > Results/Results50_16.txt
