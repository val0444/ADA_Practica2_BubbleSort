## Código en Python
import sys
import time
import random

# Aumentar el límite de recursión para soportar N grandes en Python si es necesario
sys.setrecursionlimit(2000000)

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1
    return arr

def evaluar_merge_sort(n):
    print(f"\n--- Evaluando Merge Sort para N = {n:,} ---")

    # Generar números reales aleatorios
    arr = [random.uniform(0.0, 10000.0) for _ in range(n)]

    # Memoria aproximada consumida por la lista en Python (en MB)
    # Nota: sys.getsizeof() en arreglos grandes de Python requiere mucha memoria auxiliar para objetos float.
    memoria_bytes = sys.getsizeof(arr) + sum(sys.getsizeof(i) for i in arr)
    memoria_mb = memoria_bytes / (1024 * 1024)
    print(f"Memoria estimada en RAM: {memoria_mb:.2f} MB")

    # Medir tiempo de ejecución
    inicio = time.time()
    merge_sort(arr)
    fin = time.time()

    tiempo_total = fin - inicio
    print(f"Tiempo de ejecución: {tiempo_total:.6f} segundos")

if __name__ == "__main__":
    # Probando con el primer tamaño viable
    evaluar_merge_sort(100000)

## Código en C++

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para fusionar dos subarreglos ordenados
void merge(double arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales utilizando asignación dinámica
    double *L = (double *)malloc(n1 * sizeof(double));
    double *R = (double *)malloc(n2 * sizeof(double));

    if (L == NULL || R == NULL) {
        printf("Error de asignación de memoria.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar la memoria temporal
    free(L);
    free(R);
}

// Función recursiva de Merge Sort
void mergeSort(double arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Función para evaluar tiempos y memoria consumida
void evaluarMergeSort(int n) {
    printf("\n--- Evaluando Merge Sort (en C) para N = %d ---\n", n);

    // Asignar memoria para el arreglo principal
    double *arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("No se pudo asignar memoria para el arreglo de tamaño %d\n", n);
        return;
    }

    // Inicializar generador de números aleatorios
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = ((double)rand() / RAND_MAX) * 10000.0;
    }

    // Memoria estimada consumida por el arreglo en RAM (en MB)
    double memoria_mb = (n * sizeof(double)) / (1024.0 * 1024.0);
    printf("Memoria estimada en RAM: %.2f MB\n", memoria_mb);

    // Medir tiempo de ejecución usando clock()
    clock_t inicio = clock();
    mergeSort(arr, 0, n - 1);
    clock_t fin = clock();

    double tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo_total);

    // Liberar memoria principal
    free(arr);
}

int main() {
    // Puedes cambiar el tamaño aquí (ej. 100,000 elementos)
    evaluarMergeSort(100000);
    return 0;
}
