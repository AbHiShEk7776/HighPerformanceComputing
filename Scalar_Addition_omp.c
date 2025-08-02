#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int cmp_asc(const void *a,const void *b){return *(int*)a - *(int*)b;}
int cmp_desc(const void *a,const void *b){return *(int*)b- *(int*)a;}

int main(){
      int n, i, num_threads;
    printf("Enter vector size (n): "); scanf("%d", &n);
    printf("Enter number of threads: "); scanf("%d", &num_threads);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));

    printf("Enter elements of vector A:\n");
    for (i = 0; i < n; i++) scanf("%d", &A[i]);
    printf("Enter elements of vector B:\n");
    for (i = 0; i < n; i++) scanf("%d", &B[i]);
    //Sorting for Scalar Multiplication
    qsort(A, n, sizeof(int), cmp_asc);
    qsort(B, n, sizeof(int), cmp_desc);

    long long min_scalar_product = 0;

    double start = omp_get_wtime();

    
    #pragma omp parallel for reduction(+:min_scalar_product) num_threads(num_threads) schedule(static, 2) ordered
    for (i = 0; i < n; i++) {
        long long prod = (long long)A[i] * B[i];
      
        #pragma omp ordered
        {
            printf("Thread %d: A[%d]=%d * B[%d]=%d = %lld\n", omp_get_thread_num(), i, A[i], i, B[i], prod);
        }
        min_scalar_product += prod;
    }

    double end = omp_get_wtime();

    printf("\nMinimum Scalar Product: %lld\n", min_scalar_product);
    printf("Time taken: %f seconds\n", end - start);

    free(A); free(B);


    return 0;
}