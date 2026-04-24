#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "sorting_algorithms.h"
#include "dataset_utils.h"

using namespace std;
using namespace chrono;

int main() {
    vector<string> labels;
    vector<int> values;
    int datasetChoice, algoChoice;
    string filename, algorithmName;

    cout << "===== SMART SORTING STUDIO (C++) =====\n";
    cout << "Choose Dataset:\n";
    cout << "1. Marks Dataset\n";
    cout << "2. Sales Dataset\n";
    cout << "3. Logs Dataset\n";
    cout << "Enter choice: ";
    cin >> datasetChoice;

    if (datasetChoice == 1) filename = "sample_marks.csv";
    else if (datasetChoice == 2) filename = "sample_sales.csv";
    else if (datasetChoice == 3) filename = "sample_logs.csv";
    else {
        cout << "Invalid dataset choice.\n";
        return 0;
    }

    if (!loadCSV(filename, labels, values)) {
        cout << "Error loading file: " << filename << endl;
        return 0;
    }

    displayDataset(labels, values);

    cout << "\nChoose Sorting Algorithm:\n";
    cout << "1. Merge Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Heap Sort\n";
    cout << "4. Counting Sort\n";
    cout << "5. Radix Sort\n";
    cout << "6. Bucket Sort\n";
    cout << "Enter choice: ";
    cin >> algoChoice;

    SortMetrics metrics;
    auto start = high_resolution_clock::now();

    if (algoChoice == 1) {
        algorithmName = "Merge Sort";
        mergeSort(values, 0, values.size() - 1, metrics);
    }
    else if (algoChoice == 2) {
        algorithmName = "Quick Sort";
        quickSort(values, 0, values.size() - 1, metrics);
    }
    else if (algoChoice == 3) {
        algorithmName = "Heap Sort";
        heapSort(values, metrics);
    }
    else if (algoChoice == 4) {
        algorithmName = "Counting Sort";
        countingSort(values, metrics);
    }
    else if (algoChoice == 5) {
        algorithmName = "Radix Sort";
        radixSort(values, metrics);
    }
    else if (algoChoice == 6) {
        algorithmName = "Bucket Sort";
        bucketSort(values, metrics);
    }
    else {
        cout << "Invalid algorithm choice.\n";
        return 0;
    }

    auto end = high_resolution_clock::now();
    double timeTaken = duration<double, milli>(end - start).count();

    displaySortedDataset(labels, values);

    cout << "\n===== PERFORMANCE REPORT =====\n";
    cout << "Algorithm     : " << algorithmName << endl;
    cout << "Time Taken    : " << fixed << setprecision(4) << timeTaken << " ms\n";
    cout << "Comparisons   : " << metrics.comparisons << endl;
    cout << "Swaps         : " << metrics.swaps << endl;
    cout << "Stable        : " << getStability(algorithmName) << endl;
    cout << "Description   : " << getDescription(algorithmName) << endl;

    return 0;
}