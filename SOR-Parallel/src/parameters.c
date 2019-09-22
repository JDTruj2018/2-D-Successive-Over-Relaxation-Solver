/*
Author: Jered Dominguez-Trujillo
Description: Derived Parameter Struct for Successive Over Relaxation Solution of 2-Dimensional Heat Equation
Date: April 15, 2018
*/

// Includes
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "parse.h"
#include "parameters.h"

//**************************************************************************
// calc_params() function
//   - Parses command line and converts command-line strings to
//     appropriate types
//   - Arguments:
//       - cl: command line arguments struct
//   - Returns:
//       - params: parameters struct containing relevant derived variables
//***************************************************************************
params calc_params(cl_args * cl) {
  // Initialize
  params pars;

  // Calculations
  pars.xc = cl->Lx / 2; // Used to generate forcing function g(x, y)
  pars.yc = cl->Ly / 4; // Used to generate forcing function g(x, y)
  pars.sigx = 0.1 * cl->Lx; // Used to generate forcing function g(x, y)
  pars.sigy = 0.1 * cl->Ly; // Used to generate forcing function g(x, y)
  pars.dx = cl->Lx / (double) cl->Nx; // Used to generate 2-dimensional grid
  pars.dy = cl->Ly / (double) cl->Ny; // Used to generate 2-dimensional grid
  pars.dxs = pars.dx * pars.dx; // Used for iterative calculations
  pars.dys = pars.dy * pars.dy; // Used for iterative calculations
  pars.g0 = 10; // Used to generate forcing function g(x, y)

  // Print Status and Results
  printf("=======Calculated Parameters=======\n");
  printf("xc: %.4f\n", pars.xc);
  printf("yc: %.4f\n", pars.yc);
  printf("sigx: %.8f\n", pars.sigx);
  printf("sigy: %.8f\n", pars.sigy);
  printf("dx: %.6f\n", pars.dx);
  printf("dy: %.6f\n", pars.dy);
  printf("dxs: %.8f\n", pars.dxs);
  printf("dys: %.8f\n", pars.dys);
  printf("g0: %.2f\n", pars.g0);
  printf("====================================\n");

  return pars;
}
