#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 3
#define FACTORIAL 9

int factorial = 1;

void *calculoFactorial(void *arg) {
    int start = *(int *)arg;
    int end = start + (FACTORIAL / NUM_THREADS) - 1;
    
    for (int i = start; i <= end; i++) {
        factorial *= i;
    }
    
    pthread_exit(NULL);
}

int main() {
    int start[NUM_THREADS] = {1, 4, 7};
    pthread_t threads[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculoFactorial, (void *)&start[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("El factorial de %d es: %d\n", FACTORIAL, factorial);
    
    return 0;
}
