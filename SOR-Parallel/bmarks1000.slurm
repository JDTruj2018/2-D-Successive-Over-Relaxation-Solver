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
time ./bin/run_SOR -Nx 1000 -Ny 1000 -iter 5000000 > Results/Results1000_1.txt

export OMP_NUM_THREADS=2
time ./bin/run_SOR -Nx 1000 -Ny 1000 -iter 5000000 > Results/Results1000_2.txt

export OMP_NUM_THREADS=4
time ./bin/run_SOR -Nx 1000 -Ny 1000 -iter 5000000 > Results/Results1000_4.txt

export OMP_NUM_THREADS=8
time ./bin/run_SOR -Nx 1000 -Ny 1000 -iter 5000000 > Results/Results1000_8.txt

export OMP_NUM_THREADS=16
time ./bin/run_SOR -Nx 1000 -Ny 1000 -iter 5000000 > Results/Results1000_16.txt
