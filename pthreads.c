#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
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

// Variable global para los valores V y Vr
int V[NUM_THREADS] = { 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13 };
int Vr[NUM_THREADS] = {};

// Función que ejecutará cada hilo
void* threadFunc(void* arg) {
    int index = (int)(long)arg; // Convertir puntero a entero
    Vr[index] = func(3, V[index]);
    pthread_exit(NULL);
}

// Función principal
int main() {
    pthread_t threads[NUM_THREADS];

    // Creación de los hilos
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threadFunc, (void*)(long)i); // Convertir entero a puntero
    }

    // Espera a que todos los hilos terminen
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Impresión de los resultados
    printf("Vr: ");
    for(int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", Vr[i]);
    }
    printf("\n");

    return 0;
}