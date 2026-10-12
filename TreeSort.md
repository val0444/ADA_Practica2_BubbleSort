## Codigo en python
import time
import tracemalloc
import random
import sys

# Aumentar límite de recursión para evitar errores con BST desbalanceados
sys.setrecursionlimit(200000)

class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key

def insert(root, key):
    if root is None:
        return Node(key)
    if key < root.val:
        root.left = insert(root.left, key)
    else:
        root.right = insert(root.right, key)
    return root

def store_inorder(root, res):
    if root is not None:
        store_inorder(root.left, res)
        res.append(root.val)
        store_inorder(root.right, res)

def tree_sort(arr):
    if not arr:
        return []
    root = None
    for item in arr:
        root = insert(root, item)
    res = []
    store_inorder(root, res)
    return res

def evaluate(size):
    # Generar arreglo de números reales (floats)
    arr = [random.uniform(0.0, 1000000.0) for _ in range(size)]
    
    tracemalloc.start()
    start_time = time.time()
    
    sorted_arr = tree_sort(arr)
    
    end_time = time.time()
    current, peak_memory = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    
    execution_time = end_time - start_time
    peak_memory_mb = peak_memory / (1024 * 1024)
    
    return execution_time, peak_memory_mb

if __name__ == "__main__":
    sizes = [100000, 1000000]  # Ajustar según capacidad técnica
    for size in sizes:
        t, m = evaluate(size)
        print(f"Tamaño: {size:12,d} | Tiempo: {t:8.4f} s | Memoria Máxima: {m:8.2f} MB")


## Código en C++
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sys/resource.h>

struct Node {
    double val;
    Node* left;
    Node* right;
    Node(double v) : val(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, double key) {
    if (root == nullptr) return new Node(key);
    if (key < root->val)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

void storeInorder(Node* root, std::vector<double>& arr, int& index) {
    if (root != nullptr) {
        storeInorder(root->left, arr, index);
        arr[index++] = root->val;
        storeInorder(root->right, arr, index);
    }
}

void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void treeSort(std::vector<double>& arr) {
    if (arr.empty()) return;
    Node* root = nullptr;
    for (double val : arr) {
        root = insert(root, val);
    }
    int index = 0;
    storeInorder(root, arr, index);
    freeTree(root);
}

double getPeakMemoryMB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss / 1024.0; // En Linux regresa KB
}

int main() {
    std::vector<size_t> sizes = {100000, 1000000};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1000000.0);

    for (size_t size : sizes) {
        std::vector<double> arr(size);
        for (size_t i = 0; i < size; ++i) arr[i] = dis(gen);

        auto start = std::chrono::high_resolution_clock::now();
        treeSort(arr);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Tamaño: " << size 
                  << " | Tiempo: " << elapsed.count() << " s"
                  << " | Memoria Máxima: " << getPeakMemoryMB() << " MB\n";
    }
    return 0;
}

        
