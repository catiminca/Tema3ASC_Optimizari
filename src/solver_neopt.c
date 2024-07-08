/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	
	//alocare memorie
	double *C = (double*)malloc(N * N * sizeof(double));
	double *A_T = (double*)malloc(N * N * sizeof(double));
	double *B_T = (double*)malloc(N * N * sizeof(double));
	double *temp_A_T_B = (double*)malloc(N * N * sizeof(double));
	double *temp_B_A = (double*)malloc(N * N * sizeof(double));
	double *sum = (double*)malloc(N * N * sizeof(double));

	//calculare transpuse
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			B_T[j * N + i] = B[i * N + j];
			if (i > j) {
				A_T[j * N + i] = 0;
			} else {
				A_T[j * N + i] = A[i * N + j];
			}
		}
	}

	//calculare AT *B si B * A si suma lor
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp_A_T_B[i * N + j] = 0;
			temp_B_A[i * N + j] = 0;
			
			for (int k = 0; k <= i; k++) {
				temp_A_T_B[i * N + j] += A_T[i * N + k] * B[k * N + j];
				
			} 
			for (int k = 0; k <= j; k++) {
				temp_B_A[i * N + j] += B[i * N + k] * A[k * N + j];
			}
			sum[i * N + j] = temp_A_T_B[i * N + j] + temp_B_A[i * N + j];

		}
	}
	
	//calculare C = sum * BT
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
			for (int k = 0; k < N; k++) {
				C[i * N + j] += sum[i * N + k] * B_T[k * N + j];
			}
		}
	}

	//eliberarea memoriei
	free(A_T);
	free(B_T);
	free(temp_A_T_B);
	free(temp_B_A);
	free(sum);
	return C;
}
