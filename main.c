#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double compute_u_residual(double* u, int N, int i);
double compute_v_residual(double* v, int N, int i);
double compute_P_residual(double* P, int N, int i);
double compute_u_upper_boundary_residual(double* u, int N, int i);
double compute_u_lower_boundary_residual(double* u, int N, int i);
double compute_u_left_boundary_residual(double* u, int N, int i);
double compute_u_right_boundary_residual(double* u, int N, int i);
double compute_v_left_boundary_residual(double* v, int N, int i);
double compute_v_right_boundary_residual(double* v, int N, int i);
double compute_P_left_boundary_residual(double* p, int N, int i);
double compute_P_upper_boundary_residual(double* p, int N, int i);
double compute_P_lower_boundary_residual(double* p, int N, int i);

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
    double *u = (double *)calloc(N*(N-1), sizeof(double));
    //y velocity is of the shape N-1 x N , (N-1 rows, N Columns)
    double *v = (double *)calloc(N*(N-1), sizeof(double));
    //pressure is of the shape N-1xN-1
    double *p = (double *)calloc((N-1)*(N-1), sizeof(double));
    double delta_x =  1.0 / (N-1);
    double residual_u = 100.0;
    double residual_v = 100.0;
    double residual_P = 100.0;
    int l = 0;
    //main loop
    while((l < num_iterations) || (residual_u > tol && residual_v > tol && residual_P > tol)){
        int i, j, q;
        #pragma omp parallel num_threads(k) shared(N, w, P, u, v, p, q) private(i, j) reduction(max:residual_u, residual_v, residual_P)
        {
        //u loop for red cells
        #pragma omp for schedule(static, 1)
        for (i = 0; i < N-1; i++){
            for (j = (i% 2); j < N; j+=2){
                //TODO: implement boundary cases here
                //update u, find the maximum residual
                int idx = i*N + j;
                double temp_u_residual;
                // maybe integrate these into special cases?
                //first special boundry: top left corner
                if ((i == 0) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom left corner
                else if ((i == N-2) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //top right corner
                else if ((i == 0) && (j==N-1)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom right corner
                else if ((i == N-2) && (j==N-1)){
                  //TODO 
                  //Implement the formula 
                }
                //left face update
                else if (j == 0){
                    temp_u_residual = compute_u_left_boundary_residual(u, N, idx);
                }
                //right face update
                else if (j == N-1){
                    temp_u_residual = compute_u_right_boundary_residual(u, N, idx);
                }
                //upper face
                else if (i == 0){
                    temp_u_residual = compute_u_upper_boundary_residual(u, N, idx);
                }
                //lower face
                else if (i == N-2){
                    temp_u_residual = compute_u_lower_boundary_residual(u, N, idx);
                }

                else{
                temp_u_residual = compute_u_residual(u, N, idx);
                u[idx] += w*temp_u_residual;
                if (temp_u_residual > residual_u){
                    residual_u = temp_u_residual;
                }
            }
            }

        }
        // v loop, N-1 columns by N rows
         #pragma omp for schedule(static, 1)
        for (i = 0; i < N; i++){
            for (j = (i % 2); j < N-1; j+=2){
                //TODO: implement boundary cases here
                //update u, find the maximum residual
                int idx = i*N + j;
                double temp_v_residual;
                // maybe integrate these into special cases?
                //first special boundry: top left corner
                if ((i == 0) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom left corner
                else if ((i == N-1) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //top right corner
                else if ((i == 0) && (j==N-2)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom right corner
                else if ((i == N-1) && (j==N-2)){
                  //TODO 
                  //Implement the formula 
                }
                //left face update
                else if (j == 0){
                    temp_v_residual = compute_v_left_boundary_residual(v, N, idx);
                }
                //right face update
                else if (j == N-2){
                    temp_v_residual = compute_v_right_boundary_residual(v, N, idx);
                }
                //upper face
                else if (i == 0){
                    temp_v_residual = compute_v_upper_boundary_residual(v, N, idx);
                }
                //lower face
                else if (i == N-1){
                    temp_v_residual = compute_v_lower_boundary_residual(v, N, idx);
                }

                else{
                temp_v_residual = compute_v_residual(v, N, idx);
                v[idx] += w*temp_v_residual;
                if (temp_v_residual > residual_v){
                    residual_v = temp_v_residual;
                }
            }
            }

        }
        //P loop, P is N-1 x N-1
        #pragma omp for schedule(static, 1)
        for (i = 0; i < N-1; i++){
            for (j = (i % 2); j < N-1; j+=2){
                //TODO: implement boundary cases here
                //update P, find the maximum residual
                int idx = i*N + j;
                double temp_P_residual;
                // maybe integrate these into special cases?
                //first special boundry: top left corner
                if ((i == 0) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom left corner
                else if ((i == N-2) && (j==0)){
                  //TODO 
                  //Implement the formula 
                }
                //top right corner
                else if ((i == 0) && (j==N-2)){
                  //TODO 
                  //Implement the formula 
                }
                //bottom right corner
                else if ((i == N-2) && (j==N-2)){
                  //TODO 
                  //Implement the formula 
                }
                //left face update
                else if (j == 0){
                    temp_P_residual = compute_P_left_boundary_residual(p, N, idx);
                }
                //right face update
                else if (j == N-2){
                    temp_P_residual = compute_P_right_boundary_residual(p, N, idx);
                }
                //upper face
                else if (i == 0){
                    temp_P_residual = compute_P_upper_boundary_residual(p, N, idx);
                }
                //lower face
                else if (i == N-2){
                    temp_P_residual = compute_P_lower_boundary_residual(p, N, idx);
                }

                else{
                temp_P_residual = compute_P_residual(p, N, idx);
                p[idx] += w*temp_P_residual;
                if (temp_P_residual > residual_P){
                    residual_P = temp_P_residual;
                }
            }
            }

        }
        //add in the black cells here, or some logic that can run through them all at the same time
    }
    
        l++;
    }
    //free arrays
    free(u);
    free(v);
    free(p);

    return 0;
}