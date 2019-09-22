/*
Author: Jered Dominguez-Trujillo
Date: April 15, 2018
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "parse.h"

typedef struct {
    double xc; // X Center, Used to Generate Forcing Function g(x, y)
    double yc; // Y Center, Used to Generate Forcing Function g(x, y)
    double sigx; // Sigx, Used to Generate Forcing Function g(x, y)
    double sigy; // Sigy, Used to Generate Forcing Function g(x, y)
    double dx; // Delta X, Used to Generate 2-Dimensional Grid
    double dy; // Delta Y, Used to Generate 2-Dimensional Grid
    double dxs;// Delta X Squared, Used for Iteration Calculations
    double dys;// Delta Y Squared, Used for Iteration Calculations
    double g0;// G0, Used to Generate Forcing Function g(x, y)
} params;

params calc_params(cl_args * cl);

#endif
