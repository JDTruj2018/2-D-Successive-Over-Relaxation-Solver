/*
Author: Jered Dominguez-Trujillo
Description: Parallel Red-Black Iteration Method for Successive Over Relaxation Solution of 2-Dimensional Heat Equation
Date: April 15, 2018
*/

// Includes
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#include "parse.h"
#include "parameters.h"
#include "generate.h"
#include "soriter.h"

//**************************************************************************
// sor_iter() function
//   - Performs Successive Over-Relaxation Method in Parallel
//       - Does so with Red/Black Color Scheme Method
//   - Arguments:
//       - cl: command line arguments struct
//       - pars: derived parameters struct
//       - gd: generated grid struct
//       - fc: generated forcing function struct
//   - Returns:
//       - res: struct containing a 2-dimensional matrix representing the final temperature values at all points in 2-dimensional grid
//            Solution that adheres to boundary conditions
//***************************************************************************
result sor_iter(cl_args * cl, params * pars, grid * gd, func * fc) {
  // Initialize Variables
  int i, j;
  result res;

  // Allocate and Set to Zero
  res.f = (double**) calloc((cl->Nx + 2), sizeof(double*));
  for (i = 0; i < cl->Nx + 2; i++)  {
    res.f[i] = (double*) calloc((cl->Ny + 2), sizeof(double));
  }

  // Dirilecht Boundary Condition
  for (i = 0; i < cl->Nx + 1; i++) {
    res.f[i][0] = cl->fa;
  }

  // Iteration Variables
  int iter = 1;
  double error = 1000.0;

  // Begin Iterating
  while(iter <= cl->iter_max && error > cl->tol) {
    error = 0.0;

    // Perform Parallel Computation on Red Nodes
    #pragma omp parallel for default(shared) private(i, j) schedule(static) reduction(max: error)
    for (j = 1; j < cl->Ny + 1; j++) {
      for (i = 1; i < cl->Nx + 1; i+=2) {
        if (i == 1 && j % 2 == 0) {
          i += 1;
        }
        double fij_old = res.f[i][j];
        double temp = fc->g[i][j] * pars->dxs + (res.f[i-1][j] + res.f[i+1][j]) + (res.f[i][j-1] + res.f[i][j+1]) * pars->dxs / pars->dys;
        double f_temp = temp / (1 + pars->dxs / pars->dys) / 2;
        res.f[i][j] = f_temp * cl->relax_sor + res.f[i][j] * (1- cl->relax_sor);
        double e_temp = fabs(res.f[i][j] - fij_old);
        if (error < e_temp) {
          error = e_temp;
        }
      }
    }

    // Synchronize Threads
    #pragma omp barrier

    // Perform Parallel Computation on Black Nodes
    #pragma omp parallel for default(shared) private(i, j) schedule(static) reduction(max: error)
    for (j = 1; j < cl->Ny + 1; j++) {
      for (i = 1; i < cl->Nx + 1; i+=2) {
        if (i == 1 && j % 2 == 1) {
          i += 1;
        }
        double fij_old = res.f[i][j];
        double temp = fc->g[i][j] * pars->dxs + (res.f[i-1][j] + res.f[i+1][j]) + (res.f[i][j-1] + res.f[i][j+1]) * pars->dxs / pars->dys;
        double f_temp = temp / (1 + pars->dxs / pars->dys) / 2;
        res.f[i][j] = f_temp * cl->relax_sor + res.f[i][j] * (1- cl->relax_sor);
        double e_temp = fabs(res.f[i][j] - fij_old);
        if (error < e_temp) {
          error = e_temp;
        }
      }

        // Periodic Boundary Condition
        res.f[0][j] = res.f[cl->Nx][j];
        res.f[cl->Nx+1][j] = res.f[1][j];
    }

    // Dirilecht Boundary Condition
    for (i = 0; i < cl->Nx + 1; i++) {
        res.f[i][0] = cl->fa;
    }

    // Neumann Boundary Condition
    for (i = 0; i < cl->Nx + 1; i++) {
        res.f[i][cl->Ny + 1] = res.f[i][cl->Ny] + cl->q * (2 * pars->dy);
    }

    // Print Iteration Information
    printf("Finished Iteration %d with Error %.15f\n", iter, error);

    // Increment
    iter = iter + 1;
  }

  return res;
}
