# Capstone

The problem statement can be found in the announce repo:

https://github.com/sc3260s18/announce/tree/master/capstone

## My Capstone Description and Details

Ignore the SOR-Serial Directory. This code was primarily used to outline my ideas. 

Both the Serial and Parallel Benchmarks were performed using the slurm scripts in the root SOR-Parallel Directory. Numerical results can be found in Results/ in addition to the most recent run time data in the output?.txt files in the Results/ directory. I've checked that the parallel and serial code provide the same numerical solution and results. Note that I ran the slurm files more than once to ensure accuracy, so some of the reported time values in the output?.txt files may match the reported values in the benchmarks excel file, while some may not. I reported the value that best represented accuracy and consistency.

All benchmarks and slurm files were submitted from vmp902.

To run the code on your own, go to the SOR-Parallel Directory

```
cd SOR-Parallel
```

To build, load OpenMP and the icc compiler and run

```
make cleanall
make
```

Specify the amount of threads desired

```
export $OMP_NUM_THREADS=<THREADS>
```

Run the code with the following command

```
./bin/run_SOR
```

Command line options include
- -Lx (Box Dimension, X-Length) Default: 2.0
- -Ly (Box Dimension, Y-Length) Default: 1.0
- -Nx (Number of X-Grid Points) Default: 16
- -Ny (Number of Y-Grid Points) Default: 16
- -fa (Dirilecht Temperature Boundary Condition) Default: 0.2
- -q (Neumann Heat Flux Boundary Condition) Defualt: 0
- -iter (Maximum Iterations) Default: 5000
- -tol (Tolerance) Default: 1e-6
- -sor (Relaxation Factor between 0-2) Default: 1.5

## Cloning Repository and Pushing to Your Own Private Repo

Start by cloning this repo to your cluster home directory. Click the green "Clone or
download" button on this page in GitHub, then copy the URL provided and paste it after
typing `git clone`. If you get an HTTPS error, make sure you have the following line
in your ~/.bashrc file and then type `source ~/.bashrc`.

```
module load GCC git
```

Once you have the source files, you can begin making changes. You should
periodically commit your changes and push to GitHub. Your final solution must
be pushed to GitHub before class the date the assignment is due.
 
To stage, commit, and push to GitHub (must be inside repo):

    git status   # to check untracked files
	git add file1 file2 file3      # you can add as few as one file; avoid including large data files
	git commit -m "Initial copy of files into my private repo"     # make message meaningful
	git push

Then check GitHub to make sure everything looks okay. Remember to commit
and push often as you are editing the files to complete the assignment. You
may add additional files to the repo if you'd like.

