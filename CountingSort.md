## Codigo en C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(float arr[], long n, int scale) {
    if (n <= 0) return;
    
    int *int_arr = (int *)malloc(n * sizeof(int));
    if (!int_arr) return;

    int min_val = (int)(arr[0] * scale);
    int max_val = min_val;

    for (long i = 0; i < n; i++) {
        int_arr[i] = (int)(arr[i] * scale);
        if (int_arr[i] < min_val) min_val = int_arr[i];
        if (int_arr[i] > max_val) max_val = int_arr[i];
    }

    long range = (long)max_val - min_val + 1;
    int *count = (int *)calloc(range, sizeof(int));
    if (!count) {
        free(int_arr);
        return;
    }

    for (long i = 0; i < n; i++) {
        count[int_arr[i] - min_val]++;
    }

    long index = 0;
    for (long i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index++] = (float)(i + min_val) / scale;
            count[i]--;
        }
    }

    free(int_arr);
    free(count);
}

int main() {
    long n_sizes[] = {100000, 1000000, 10000000, 100000000};
    int num_sizes = 4;

    for (int s = 0; s < num_sizes; s++) {
        long n = n_sizes[s];
        printf("\n--- Counting Sort en C | N = %ld ---\n", n);
        
        float *arr = (float *)malloc(n * sizeof(float));
        if (arr == NULL) {
            printf("Error: No se pudo asignar memoria (Posible Killed).\n");
            continue;
        }

        for (long i = 0; i < n; i++) {
            arr[i] = ((float)rand() / RAND_MAX) * 10.0f;
        }

        clock_t start = clock();
        countingSort(arr, n, 100);
        clock_t end = clock();

        double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        double memory_mb = (n * sizeof(float) + n * sizeof(int)) / (1024.0 * 1024.0);

        printf("Tiempo de ejecución: %.4f segundos\n", time_elapsed);
        printf("Memoria consumida (datos base): %.2f MB\n", memory_mb);

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

void countingSort(vector<float>& arr, int scale = 100) {
    long n = arr.size();
    if (n <= 0) return;

    vector<int> int_arr(n);
    int min_val = static_cast<int>(arr[0] * scale);
    int max_val = min_val;

    for (long i = 0; i < n; i++) {
        int_arr[i] = static_cast<int>(arr[i] * scale);
        min_val = min(min_val, int_arr[i]);
        max_val = max(max_val, int_arr[i]);
    }

    long range = static_cast<long>(max_val) - min_val + 1;
    vector<int> count(range, 0);

    for (long i = 0; i < n; i++) {
        count[int_arr[i] - min_val]++;
    }

    long index = 0;
    for (long i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index++] = static_cast<float>(i + min_val) / scale;
            count[i]--;
        }
    }
}

int main() {
    vector<long> n_sizes = {100000, 1000000, 10000000, 100000000};

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 10.0f);

    for (long n : n_sizes) {
        cout << "\n--- Counting Sort en C++ | N = " << n << " ---" << endl;
        try {
            vector<float> arr(n);
            for (long i = 0; i < n; i++) {
                arr[i] = dis(gen);
            }

            auto start = chrono::high_resolution_clock::now();
            countingSort(arr, 100);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = end - start;
            double memory_mb = (n * sizeof(float) + n * sizeof(int)) / (1024.0 * 1024.0);

            cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
            cout << "Memoria consumida (datos base): " << memory_mb << " MB" << endl;
        } catch (const bad_alloc& e) {
            cout << "Excepción: Memoria insuficiente (std::bad_alloc / Killed)." << endl;
        }
    }

    return 0;
}
