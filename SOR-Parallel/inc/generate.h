/*
Author: Jered Dominguez-Trujillo
Date: April 15, 2018
*/

#ifndef GENERATE_H
#define GENERATE_H

#include "parse.h"
#include "parameters.h"

typedef struct {
    double * x; // Grid X Coordinates (1-Dimensional Vector)
    double * y; // Grid Y Coordinates (1-Dimensional Vector)
} grid;

typedef struct {
  double ** g; // Forcing Function g(x, y) (2-Dimensional Matrix)
} func;

grid generate_grid(cl_args * cl, params * pars);
func generate_func(cl_args * cl, params * pars, grid * gd);

#endif
