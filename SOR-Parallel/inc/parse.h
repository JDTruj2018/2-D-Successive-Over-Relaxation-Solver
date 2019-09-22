/*
Author: Jered Dominguez-Trujillo
Date: April 15, 2018
*/

#ifndef PARSE_H
#define PARSE_H

typedef struct {
    double Lx; // X-Direction Box Length
    double Ly; // Y-Direction Box Length
    int Nx; // Nodes in X-Direction
    int Ny; // Nodes in Y-Direction
    double fa; // Dirilecht Boundary Condition
    double q; // Neumann Boundary Condition
    int iter_max; // Maximum Iterations
    double tol; // Tolerance
    double relax_sor; // w: Between 0-2
} cl_args;

cl_args parse_command_line(const int, char **);

#endif
