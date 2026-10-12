## Codigo en C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(float arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        float temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(float arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        float temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    long n_sizes[] = {100000, 1000000, 10000000, 100000000};
    int num_sizes = 4;

    for (int s = 0; s < num_sizes; s++) {
        long n = n_sizes[s];
        printf("\n--- Heapsort en C | N = %ld ---\n", n);
        
        float *arr = (float *)malloc(n * sizeof(float));
        if (arr == NULL) {
            printf("Error: No se pudo asignar memoria (Posible Killed).\n");
            continue;
        }

        for (long i = 0; i < n; i++) {
            arr[i] = ((float)rand() / RAND_MAX) * 100.0f;
        }

        clock_t start = clock();
        heapSort(arr, n);
        clock_t end = clock();

        double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double memory_mb = (n * sizeof(float)) / (1024.0 * 1024.0);

        printf("Tiempo de ejecución: %.4f segundos\n", time_elapsed);
        printf("Memoria consumida (aproximada): %.2f MB\n", memory_mb);

        free(arr);
    }
    return 0;
}



## Codigo en C++

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <new>

using namespace std;

void heapify(vector<float>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    vector<long> n_sizes = {100000, 1000000, 10000000, 100000000};

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 100.0f);

    for (long n : n_sizes) {
        cout << "\n--- Heapsort en C++ | N = " << n << " ---" << endl;
        try {
            vector<float> arr(n);
            for (long i = 0; i < n; i++) {
                arr[i] = dis(gen);
            }

            auto start = chrono::high_resolution_clock::now();
            heapSort(arr);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = end - start;
            double memory_mb = (n * sizeof(float)) / (1024.0 * 1024.0);

            cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
            cout << "Memoria consumida (aproximada): " << memory_mb << " MB" << endl;
        } catch (const bad_alloc& e) {
            cout << "Excepción: Memoria insuficiente (std::bad_alloc / Killed)." << endl;
        }
    }

    return 0;
}
