/*
Author: Jered Dominguez-Trujillo
Description: Grid and Function Structs for Successive Over Relaxation Solution of 2-Dimensional Heat Equation
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

//**************************************************************************
// generate_grid() function
//   - Generates x and y vectors representing rectangular generate_grid
//      - Uses Nx, dx, Ny, and dy
//   - Arguments:
//       - cl: command line arguments struct
//       - pars: derived parameters struct
//   - Return:
//       - gd: grid struct containing two 1-dimensional vectors (x and y)
//***************************************************************************
grid generate_grid(cl_args * cl, params * pars) {
  // Initialize Variables
  int i, j;
  grid gd;

  // Allocate memory
  gd.x = malloc(cl->Nx * sizeof(double));
  gd.y = malloc(cl->Ny * sizeof(double));

  // Generate x vector
  for (i = 0; i < cl->Nx; i++) {
      gd.x[i] = i * pars->dx;
  }

  // Generate y vector
  for (j = 0; j < cl->Ny; j++) {
      gd.y[j] = j * pars->dy;
  }

  return gd;
}

//**************************************************************************
// generate_func() function
//   - Generates 2-dimensional heat function that serves as the initial temperature condition along the grid
//      - Exponential function with peak at xc, yc
//      - Can be modified by changing
//          - g0, sigx, sigy, xc, yc
//   - Arguments:
//       - cl: command line arguments struct
//       - pars: derived parameters struct
//       - gd: generated grid struct
//   - Return:
//       - func: struct containing a 2-dimensional grid representing the function values at all points in the grid
//***************************************************************************
func generate_func(cl_args * cl, params * pars, grid * gd) {
  // Initialize Variables
  int i, j;
  func fc;

  // Allocate and Set to Zero
  fc.g = (double**) calloc((cl->Nx + 1), sizeof(double*));

  for (i = 0; i < cl->Nx + 1; i++)  {
    fc.g[i] = (double*) calloc((cl->Ny + 1), sizeof(double));
  }

  // Fill with function values dependent on x, y coordinates within grid g(x, y)
  for (j = 0; j < cl->Ny; j++) {
      for (i = 0; i < cl->Nx; i++) {
          double tmp = - (pow(gd->x[i] - pars->xc, 2) / pow(pars->sigx, 2)) - (pow((gd->y[j] - pars->yc), 2) / pow(pars->sigy, 2));
          fc.g[i][j] = pars->g0 * exp(tmp);
      }
  }

  return fc;
}
