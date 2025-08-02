#include<stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){
    long long num_steps;
    int i, threads;
    double step ,x ,sum=0.0;
    double pi;
    printf("Enter the number of integration steps:");
    scanf("%lld",&num_steps);
    printf("Enter the number of threads:");
    scanf("%d",&threads);
    step=1.0/(double)num_steps;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) num_threads(threads)
    for (i=0;i<num_steps;i++){
        x=(i+0.5)*step;
        sum+=4.0/(1.0+x*x);
    }
    pi=step*sum;
    double end= omp_get_wtime();
    printf("Calculated value of PI: %.40f\n", pi);
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}