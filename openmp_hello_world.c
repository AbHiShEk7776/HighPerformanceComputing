#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    {
        // int tid=omp_get_num_threads();
        printf("Hello World\n");
    }
    return 0;
}