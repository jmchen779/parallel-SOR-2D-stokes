#include <stdio.h>
#include <stdlib.h>>

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
    
    

    return 0;
}