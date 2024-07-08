/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */


double* my_solver(int N, double *A, double* B) {

	//alocarea memoriei
	double *C = (double*)malloc(N * N * sizeof(double));
	double *A_T = (double*)malloc(N * N * sizeof(double));
	double *B_T = (double*)malloc(N * N * sizeof(double));
	double *temp_A_T_B = (double*)malloc(N * N * sizeof(double));
	double *temp_B_A = (double*)malloc(N * N * sizeof(double));
	double *sum = (double*)malloc(N * N * sizeof(double));

	register int i = 0, j = 0, k = 0;
	register double* pa, *pb, *orig_pa;
	register double suma = 0;

	//calcularea transpuselor
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			B_T[j * N + i] = B[i * N + j];
			if (i > j) {
				A_T[j * N + i] = 0;
			} else {
				A_T[j * N + i] = A[i * N + j];
			}
		}
	}

	//calcularea AT * B
	for(i = 0; i < N; i++) {
  		orig_pa = &A_T[i * N];
  		for(j = 0; j < N; j++) {
    		pa = orig_pa;
    		pb = &B[j];
    		suma = 0;
    		for(k = 0; k <= i; k++) {
      			suma += *pa * *pb;
      			pa++;
      			pb += N;
				
    		}
    		temp_A_T_B[i * N + j] = suma;
  		}
	}

	//calcularea B * A
	for(i = 0; i < N; i++) {
  		orig_pa = &B[i * N];
  		for(j = 0; j < N; j++) {
			pa = orig_pa;
			pb = &A[j];
			suma = 0;
			for(k = 0; k <= j; k++) {
	  			suma += *pa * *pb;
	  			pa++;
	  			pb += N;
			}
			temp_B_A[i * N + j] = suma;
  		}
	}

	//calcularea sumei dintre matricile rezultate
	for(i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			sum[i * N + j] = temp_A_T_B[i * N + j] + temp_B_A[i * N + j];
		}
	}

	//calcularea C = sum * BT
	for(i = 0; i < N; i++) {
  		orig_pa = &sum[i * N];
  		for(j = 0; j < N; j++) {
			pa = orig_pa;
			pb = &B_T[j];
			suma = 0;
			for(k = 0; k < N; k++) {
	  			suma += *pa * *pb;
	  			pa++;
	  			pb += N;
			}
			C[i * N + j] = suma;
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
