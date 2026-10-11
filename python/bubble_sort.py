import time
import sys
import random

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def evaluar_bubble_sort(n):
    print(f"\n--- Evaluando Bubble Sort para N = {n:,} ---")
    
    # Generar números reales aleatorios
    arr = [random.uniform(0.0, 10000.0) for _ in range(n)]
    
    # Memoria aproximada consumida por la lista en Python (en MB)
    memoria_bytes = sys.getsizeof(arr) + sum(sys.getsizeof(i) for i in arr)
    memoria_mb = memoria_bytes / (1024 * 1024)
    print(f"Memoria estimada en RAM: {memoria_mb:.2f} MB")
    
    # Medir tiempo de ejecución
    inicio = time.time()
    bubble_sort(arr)
    fin = time.time()
    
    tiempo_total = fin - inicio
    print(f"Tiempo de ejecución: {tiempo_total:.6f} segundos")

if __name__ == "__main__":
    # Probando con el primer tamaño viable
    evaluar_bubble_sort(100000)
