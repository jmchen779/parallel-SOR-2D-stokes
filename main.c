#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double compute_u_residual(double* u, int i);
double compute_v_residual(double* v, int i);
double compute_P_residual(double* P, int i);


//a program that uses SOR to numerically solvethe stokes flow equations, which describe a fluid which is highly
//viscous or slowly moving. The program takes command line arguments of N (grid size), k (number of threads)
// viscosity, pressure drop, relaxation parameter, tolerance, and max iterations. The outputs will be stored in 3
//txt files, 
int main(int argc, char *argv[]){
    //read in command line arguments
    int argi = 0;
    //print error if we dont have enough parameters
    if (argc < 9){
        printf("Error: Not enough arguments supplied\n");
        return 1;
    }
    int N = atoi(argv[++argi]);     printf("N = %d\n", N);            
    int k = atoi(argv[++argi]);     printf("Number of Threads: %d\n", k);
    double viscosity = atof(argv[++argi]);     printf("Viscosity: %.6lf\n", viscosity);
    double P = atof(argv[++argi]);     printf("P: %.6lf\n", P);
    double w = atof(argv[++argi]);     printf("Relaxation Patramater: %.6lf\n", w);
    double tol = atof(argv[++argi]);     printf("Error tolerance: %.6lf\n", tol);
    int num_iterations = atoi(argv[++argi]);     printf("Number of iterations = %d\n", num_iterations);    
    //think these need to be flipped
    // x velocity is of the shape N x N -1, (N rows, N-1 Columns)
    double *u = (double *)malloc(N*(N-1)*sizeof(double));
    //y velocity is of the shape N-1 x N , (N-1 rows, N Columns)
    double *v = (double *)malloc(N*(N-1)*sizeof(double));
    //pressure is of the shape N-1xN-1
    double *p = (double *)malloc((N-1)*(N-1)*sizeof(double));
    double delta_x =  1.0 / (N-1);
    double residual_u = 100.0;
    double residual_v = 100.0;
    double residual_P = 100.0;
    //main loop
    while(residual_u > tol && residual_v > tol && residual_P > tol){
        int i, j;
        #pragma omp parallel num_threads(k) shared(N, w, P, u, v, p) private(i, j) reduction(max:residual_u, residual_v, residual_P)
        //u loop for red cells
        #pragma omp for schedule(static, 1)
        for (i = 0; i < N-1; i+=2){
            for (j = 1; j < N; j+=2){
                int idx = i + j*(N-1)
            }

        }
    }
    //free arrays
    free(u);
    free(v);
    free(p);

    return 0;
}