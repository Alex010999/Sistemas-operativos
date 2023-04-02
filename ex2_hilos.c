#include <stdio.h>
#include <pthread.h>

//declaracion de vars 
#define NUM_THREADS 3
#define ARRAY_SIZE 12

int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int search_number = 8;
int found_flag = 0;

void *search(void *args) {
    int *subarray = (int *)args;
    int i;
    for (i = 0; i < ARRAY_SIZE/NUM_THREADS; i++) {
        if (subarray[i] == search_number) {
            found_flag = 1;
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}


int main() {
    pthread_t threads[NUM_THREADS];
    int i;
    int subarrays[NUM_THREADS][ARRAY_SIZE/NUM_THREADS];

    // Divide el arreglo en 3 sub arreglos
    for (i = 0; i < NUM_THREADS; i++) {
        int j;
        for (j = 0; j < ARRAY_SIZE/NUM_THREADS; j++) {
            subarrays[i][j] = array[i*(ARRAY_SIZE/NUM_THREADS) + j];
        }
    }

    //3 hilos secundarios
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, search, (void *)subarrays[i]);
    }

    //Esperar a que hilos termine
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Verifica la variable global found_flag 
    if (found_flag) {
        printf("El número %d fue encontrado.\n", search_number);
    } else {
        printf("El número %d no fue encontrado.\n", search_number);
    }

    return 0;
}
