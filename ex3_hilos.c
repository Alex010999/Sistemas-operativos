#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 5

// se define el arreglo global
int buffer[SIZE] = {0}; 
int producer_finished = 0;

void *producer(void *arg) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("Introduce un valor para la casilla %d: ", i);
        scanf("%d", &buffer[i]);
    }
    producer_finished = 1;
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i;
    while (1) {
        for (i = 0; i < SIZE; i++) {
            if (buffer[i] != 0) {
                printf("      Valor leído de la casilla %d: %d\n", i, buffer[i]);
                buffer[i] = 0;
            }
        }
        if (producer_finished && buffer[SIZE-1] == 0) {
            printf("Hemos terminado.\n");
            pthread_exit(NULL);
        }
    }
}

int main() {
    pthread_t threads[2];
    int rc1, rc2;

    //Hilo productor
    rc1 = pthread_create(&threads[0], NULL, producer, NULL);
    if (rc1) {
        printf("Error: no se puede crear el hilo productor (%d)\n", rc1);
        exit(-1);
    }

    //Hilo consumidor
    rc2 = pthread_create(&threads[1], NULL, consumer, NULL);
    if (rc2) {
        printf("Error: no se puede crear el hilo consumidor (%d)\n", rc2);
        exit(-1);
    }

    // Espera a que los hilos terminen
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
