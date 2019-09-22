#include<stdio.h>
#include<string.h>
#include<math.h>
#include<unistd.h>

int main(int argc, char ** argv) {
    printf("Starting\n");

    double Lx = 2.0;
    double Ly = 1.0;

    double fa = 0.2;
    double q = 0.0;

    double xc = Lx / 2;
    double yc = Ly / 4;

    double sigx = 0.1 * Lx;
    double sigy = 0.1 * Ly;

    double g0 = 10;

    int Nx = 64;
    int Ny = 64;

    int iter_max = 5000;
    double tol = 0.000001;

    double dx = Lx / (double) Nx;
    double dy = Ly / (double) Ny;

    double dxs = dx * dx;
    double dys = dy * dy;

    double x[Nx];
    double y[Ny];

    int i;
    int j;
    for (i = 0; i < Nx; i++) {
        x[i] = i * dx;
    }

    for (j = 0; j < Ny; j++) {
        y[j] = j * dy;
    }

    double g[Nx+1][Ny+1];

    memset(g, 0.0, (Nx + 1) * (Ny + 1) * sizeof(double));

    for (j = 0; j < Ny; j++) {
        for (i = 0; i < Nx; i++) {
            double tmp = - (pow(x[i] - xc, 2) / pow(sigx, 2)) - (pow((y[j] - yc), 2) / pow(sigy, 2));
            g[i][j] = g0 * exp(tmp);
        }
    }


    double f[Nx + 2][Ny + 2];
    memset(f, 0.0, (Nx + 2) * (Ny + 2) * sizeof(double));

    for (i = 0; i < Nx + 1; i++) {
      f[i][0] = fa;
    }

    double relax_sor = 1.5;
    double iter_save[iter_max + 1];
    double error_save[iter_max + 1];

    int iter = 1;
    double error = 1000.0;

    while(iter <= iter_max && error > tol) {
      error = 0.0;
      for (j = 1; j < Ny + 1; j++) {
        for (i = 1; i < Nx + 1; i++) {
          double fij_old = f[i][j];
          double temp = g[i][j] * dxs + (f[i-1][j] + f[i+1][j]) + (f[i][j-1] + f[i][j+1]) * dxs / dys;
          double f_temp = temp / (1 + dxs / dys) / 2;
          f[i][j] = f_temp * relax_sor + f[i][j] * (1- relax_sor);
          double e_temp = fabs(f[i][j] - fij_old);
          if (error < e_temp) {
            error = e_temp;
          }
        }

          f[0][j] = f[Nx][j];
          f[Nx+1][j] = f[1][j];
        }

        for (i = 0; i < Nx + 1; i++) {
          f[i][0] = fa;
        }

        for (i = 0; i < Nx + 1; i++) {
          f[i][Ny + 1] = f[i][Ny] + q * (2 * dy);
        }

        error_save[iter - 1] = error;
        iter_save[iter - 1] = iter;

        printf("Finished Iteration %d with Error %.15f\n", iter, error);
        iter = iter + 1;
    }

    for (i = 0; i < Nx + 1; i++) {
      printf("%.15f ", f[3][i]);
    }
    printf("\n");

    return 0;
}
