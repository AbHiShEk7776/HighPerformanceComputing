#include<stdio.h>
#include<omp.h>
int main(){
    int num_threads;
    printf("Enter the Number of threads:");
    scanf("%d",&num_threads);
    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hellow World from thread %d \n",tid);
    }
    return 0;
}