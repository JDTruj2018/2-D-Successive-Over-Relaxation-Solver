/*
Author: Jered Dominguez-Trujillo
Description: CL Parameter Struct for Successive Over Relaxation Solution of 2-Dimensional Heat Equation
Date: April 15, 2018
*/

// Includes
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "parse.h"

//**************************************************************************
// parse_command_line() function
//   - Parses command line and converts command-line strings to
//     appropriate types
//   - Arguments:
//       - arg_count: number of arguments passed from command line
//       - arg_array: array of strings containing arguments from command line
//   - Returns:
//       - cl: command line struct containing relevant variables
//***************************************************************************
cl_args parse_command_line(const int arg_count, char ** arg_array) {
    // Defaults
    cl_args cl;
    cl.Lx = 2.0;
    cl.Ly = 1.0;
    cl.Nx = 16;
    cl.Ny = 16;
    cl.fa = 0.2;
    cl.q = 0.0;
    cl.iter_max = 5000;
    cl.tol = 0.000001;
    cl.relax_sor = 1.5;

    // Parse CLI Input Arguments
    int count = 1;
    while (count < arg_count) {
      if (!strcmp(arg_array[count], "-Lx")) {
        cl.Lx = atof(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-Ly")) {
        cl.Ly = atof(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-Nx")) {
        cl.Nx = atoi(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-Ny")) {
        cl.Ny = atoi(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-f")) {
        cl.fa = atof(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-q")) {
        cl.q = atof(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-iter")) {
        cl.iter_max = atoi(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-tol")) {
        cl.tol = atof(arg_array[count + 1]);
      }
      if (!strcmp(arg_array[count], "-sor")) {
        cl.relax_sor = atof(arg_array[count + 1]);
      }

      count += 2;
    }

    // Print Results
    printf("=======Command line arguments=======\n");
    printf("Lx: %.2f\n", cl.Lx);
    printf("Ly: %.2f\n", cl.Ly);
    printf("Nx: %d\n", cl.Nx);
    printf("Ny: %d\n", cl.Ny);
    printf("fa: %.2f\n", cl.fa);
    printf("q: %.2f\n", cl.q);
    printf("iter_max: %d\n", cl.iter_max);
    printf("tolerance: %.8f\n", cl.tol);
    printf("relax_sor: %.2f\n", cl.relax_sor);
    printf("====================================\n");

    return cl;
}
