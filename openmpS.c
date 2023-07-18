#include <stdio.h>
#include <omp.h>

#define THREADS 2

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

// Función principal
int main() {
    int V[16] = { 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13 };
    int Vr[16] = {};
 
    printf("Vr: ");
    
    #pragma omp parallel for schedule(static) num_threads(THREADS)
    for(int i = 0; i < 16; i++) {
        Vr[i] = func(3, V[i]);
    }
    
    // Imprimir el resultado después del bloque paralelo para asegurar un orden correcto
    for(int i = 0; i < 16; i++) {
        printf("%d ", Vr[i]);
    }
    printf("\n");

    return 0;
}
