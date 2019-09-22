/*
Author: Jered Dominguez-Trujillo
Description: Miscellaneous Clean and Print Functions for Successive Over Relaxation Solution of 2-Dimensional Heat Equation
Date: April 15, 2018
*/

// Includes
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "parse.h"
#include "parameters.h"
#include "generate.h"
#include "soriter.h"
#include "misc.h"

//**************************************************************************
// print_results() function
//   - Prints Temperature Distribution Matrix
//   - Arguments:
//       - cl: command line arguments struct
//       - res: resultant temperature distribution matrix
//***************************************************************************
void print_results(cl_args * cl, result * res) {
  // Initialize Variables
  int i, j;

  // Print Final Temperature Distribution
  for (i = 0; i < cl->Nx; i++) {
    for (j = 0; j < cl->Ny; j++) {
      printf("%.8f, ", res->f[i][j]);
    }
    printf("\n");
  }
}

//**************************************************************************
// clean_mem() function
//   - Frees all dynamically allocated memory
//   - Arguments:
//       - cl: command line arguments struct
//       - pars: derived parameters struct
//       - gd: generated grid struct
//       - fc: generated forcing function struct
//       - res: resultant temperature distribution matrix
//***************************************************************************
void clean_mem(cl_args * cl, grid * gd, func * fc, result * res) {
  // Initialize Variables
  int i, j;

  // Free Grid Vectors
  free(gd->x);
  free(gd->y);

  // Free Forcing Function Matrix
  for (i = 0; i < cl->Nx + 1; i++) {
     free(fc->g[i]);
  }
  free(fc->g);

  // Free Temperature Distribution Matrix
  for (i = 0; i < cl->Nx + 2; i++) {
     free(res->f[i]);
  }
  free(res->f);
}
