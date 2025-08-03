#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


void matrix_add(int **A, int **B, int **C, int N, int num_threads) {
    #pragma omp parallel for collapse(2) num_threads(num_threads)
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int **alloc_matrix(int N) {
    int **mat = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        mat[i] = malloc(N * sizeof(int));
    return mat;
}

void free_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++) free(mat[i]);
    free(mat);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};
    double times[5][4];

    for(int s=0; s<5; s++) {
        int N = sizes[s];
        int **A = alloc_matrix(N);
        int **B = alloc_matrix(N);
        int **C = alloc_matrix(N);
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }

        for(int t=0; t<4; t++) {
            double start = omp_get_wtime();
            matrix_add(A, B, C, N, threads[t]);
            double end = omp_get_wtime();
            times[s][t] = end - start;
            printf("Matrix Size: %d, Threads: %d, Time: %f sec\n", N, threads[t], times[s][t]);
        }
        free_matrix(A, N); free_matrix(B, N); free_matrix(C, N);
    }

    
    printf("\nTiming Summary (rows = sizes, cols = threads 1,2,4,8):\n");
    for(int s=0; s<5; s++) {
        for(int t=0; t<4; t++)
            printf("%f ", times[s][t]);
        printf("\n");
    }
    return 0;
}
