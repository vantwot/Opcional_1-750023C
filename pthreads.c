#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ARRAY_SIZE 16
#define WORK_PER_THREAD (ARRAY_SIZE/NUM_THREADS)

// Implementación de la función func(m,n)
int func(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

// Variables globales para los valores V y Vr
int V[ARRAY_SIZE] = { 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13 };
int Vr[ARRAY_SIZE] = {};

// Función que ejecutará cada hilo
void* threadFunc(void* arg) {
    int index = (int)(long)arg;
    for(int i = index*WORK_PER_THREAD; i < (index+1)*WORK_PER_THREAD; i++) {
        Vr[i] = func(3, V[i]);
    }
    pthread_exit(NULL);
}

// Función principal
int main() {
    pthread_t threads[NUM_THREADS];

    // Creación de los hilos
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threadFunc, (void*)(long)i);
    }

    // Espera a que todos los hilos terminen
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Impresión de los resultados
    printf("Vr: ");
    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", Vr[i]);
    }
    printf("\n");

    return 0;
}
