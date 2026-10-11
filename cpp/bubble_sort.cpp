#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void evaluarBubbleSort(int n) {
    cout << "\n--- Evaluando Bubble Sort para N = " << n << " ---" << endl;
    
    vector<double> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 10000.0);
    
    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }
    
    // Memoria consumida por el vector (capacidad * tamaño de double)
    double memoria_mb = (arr.capacity() * sizeof(double)) / (1024.0 * 1024.0);
    cout << "Memoria estimada en RAM: " << memoria_mb << " MB" << endl;

    auto inicio = high_resolution_clock::now();
    bubbleSort(arr);
    auto fin = high_resolution_clock::now();

    duration<double> duracion = fin - inicio;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;
}

int main() {
    evaluarBubbleSort(100000); // 100,000 elementos
    return 0;
}
