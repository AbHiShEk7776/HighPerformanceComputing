#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_first_elements(int *vec, int N) {
    printf("First 8 elements: ");
    for(int i=0; i<8 && i<N; i++) printf("%d ", vec[i]);
    printf("\n");
}

int main() {
    int N = 200;
    int scalar = 5;
    int num_threads[] = {1, 2, 4, 8};  
    int chunk_sizes[] = {1, 5, 10, 25, 50, 100}; 
    int n_chunks = sizeof(chunk_sizes)/sizeof(int);
    int n_threads = sizeof(num_threads)/sizeof(int);

    printf("[Static Scheduling, Various Chunk Sizes]\n");
    for(int c = 0; c < n_chunks; c++) {
        int chunk = chunk_sizes[c];
        printf("=== Chunk size: %d ===\n", chunk);
        double t_base = 0;
        for(int t = 0; t < n_threads; t++) {
            int threads = num_threads[t];
            int *vec = malloc(N*sizeof(int));
            for(int i=0;i<N;i++) vec[i]=i;

            double start = omp_get_wtime();
            #pragma omp parallel for num_threads(threads) schedule(static,chunk)
            for(int i=0; i<N; i++) {
                vec[i] += scalar;
            }
            double end = omp_get_wtime();
            if (t == 0) t_base = end - start;
            double speedup = t_base / (end - start);
            printf("Threads: %d, Time: %f s, Speedup: %.2f\n", threads, end - start, speedup);

            if (t == 0 && c == 0) print_first_elements(vec, N);
            free(vec);
        }
        printf("\n");
    }

    printf("\n[Dynamic Scheduling, Various Chunk Sizes]\n");
    for(int c = 0; c < n_chunks; c++) {
        int chunk = chunk_sizes[c];
        printf("=== Chunk size: %d ===\n", chunk);
        double t_base = 0;
        for(int t = 0; t < n_threads; t++) {
            int threads = num_threads[t];
            int *vec = malloc(N*sizeof(int));
            for(int i=0;i<N;i++) vec[i]=i;

            double start = omp_get_wtime();
            #pragma omp parallel for num_threads(threads) schedule(dynamic,chunk)
            for(int i=0; i<N; i++) {
                vec[i] += scalar;
            }
            double end = omp_get_wtime();
            if (t == 0) t_base = end - start;
            double speedup = t_base / (end - start);
            printf("Threads: %d, Time: %f s, Speedup: %.2f\n", threads, end - start, speedup);

            if (t == 0 && c == 0) print_first_elements(vec, N);
            free(vec);
        }
        printf("\n");
    }

    // Demonstrate nowait
    printf("\n[Demonstrate `nowait` Clause]\n");
    int vec1[N], vec2[N];
    for(int i=0;i<N;i++) { vec1[i]=i; vec2[i]=i; }

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for schedule(static, 10) nowait
        for(int i=0; i<N; i++)
            vec1[i] += scalar;

        
        #pragma omp for schedule(static, 10)
        for(int i=0; i<N; i++)
            vec2[i] -= scalar;

        #pragma omp single
        {
            printf("First 8 elements of vec1 after nowait-add: ");
            for(int i=0;i<8;i++) printf("%d ", vec1[i]);
            printf("\n");

            printf("First 8 elements of vec2 after nowait-subtract: ");
            for(int i=0;i<8;i++) printf("%d ", vec2[i]);
            printf("\n");
        }
    }

    return 0;
}
