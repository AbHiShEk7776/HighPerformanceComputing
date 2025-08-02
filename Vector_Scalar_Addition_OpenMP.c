#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 int main(){
        int N, scalar, i ,threads;
        printf("Enter the Vector Size: ");
        scanf("%d",&N);
        printf("Enter scalar to add: "); 
        scanf("%d", &scalar);
        printf("Enter number of threads: "); 
        scanf("%d", &threads);

    int *A= malloc(N*sizeof(int));
    for(i=0;i<N;i++){
        A[i]=i;
    }
    double start=omp_get_wtime();
    #pragma omp parallel for num_threads(threads)

    for(i=0;i<N;i++){
        A[i]=A[i]+scalar;
    }
    double end =omp_get_wtime();

     printf("First 10 elements after scalar addition:\n");
    for (i = 0; i < (N > 10 ? 10 : N); i++) printf("%d ", A[i]);
    printf("\nTime taken: %f seconds\n", end - start);

    free(A);


    return 0;
 }