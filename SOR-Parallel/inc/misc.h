/*
Author: Jered Dominguez-Trujillo
Date: April 15, 2018
*/

#ifndef MISC_H
#define MISC_H

#include "parse.h"
#include "parameters.h"
#include "generate.h"
#include "soriter.h"

void print_results(cl_args * cl, result * res);
void clean_mem(cl_args * cl, grid * gd, func * fc, result * res);

#endif
