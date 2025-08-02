#include<stdio.h>
int main(){
    int num_threads;
    printf("Enter the Number of threads\n");
    scanf("%d", &num_threads);
    for(int i=0;i<num_threads;i++){
        printf("Hello World from Thread %d \n",i);
    }
    return 0;
}