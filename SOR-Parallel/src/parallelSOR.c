/*
Author: Jered Dominguez-Trujillo
Description: Successive Over Relaxation Solution of 2-Dimensional Heat Equation
Date: April 15, 2018
*/

// Includes
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include <omp.h>

#include "parse.h"
#include "parameters.h"
#include "generate.h"
#include "soriter.h"
#include "misc.h"

int main(int argc, char ** argv) {
    cl_args cl = parse_command_line( argc, argv);
    params pars = calc_params(&cl);
    grid gd = generate_grid(&cl, &pars);
    func fc = generate_func(&cl, &pars, &gd);
    result res = sor_iter(&cl, &pars, &gd, & fc);

    print_results(&cl, & res);
    clean_mem(&cl, &gd, &fc, &res);

    return 0;
}
