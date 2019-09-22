/*
Author: Jered Dominguez-Trujillo
Date: April 15, 2018
*/

#ifndef SORITER_H
#define SORITER_H

#include "parse.h"
#include "parameters.h"
#include "generate.h"

typedef struct {
  double ** f; // Resultant 2-Dimensional Temperature Distribution
} result;

result sor_iter(cl_args * cl, params * pars, grid * gd, func * fc);

#endif
