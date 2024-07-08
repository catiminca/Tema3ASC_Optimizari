/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {

	//alocare memorie
	double *C = (double*)calloc(N * N , sizeof(double));
	double *temp_A_T_B = (double*)malloc(N * N * sizeof(double));
	double *temp_B_A = (double*)malloc(N * N * sizeof(double));
	double ALPHA = 1.0;

	//copiez in temp_A_T_B pe B
	cblas_dcopy(N * N, B, 1, temp_A_T_B, 1);
	
	//copiez in temp_B_A pe B
	cblas_dcopy(N * N, B, 1, temp_B_A, 1);

	//inmultesc pe A_T cu temp_A_T_B(B) si stochez rezultatul in temp_A_T_B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, ALPHA, A, N, temp_A_T_B, N);
	
	//inmultesc pe temp_B_A cu A si stochez rezultatul in temp_B_A
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, ALPHA, A, N, temp_B_A, N);

	//adun matricile rezultate
	cblas_daxpy(N * N, ALPHA, temp_A_T_B, 1, temp_B_A, 1);

	//inmultesc rezultatul cu B transpus si stochez in C
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, ALPHA, temp_B_A, N, B, N, ALPHA, C, N);

	free(temp_A_T_B);
	free(temp_B_A);

	return C;
}
