#include "sorting_algorithms.h"
#include <algorithm>
#include <cmath>
using namespace std;

// ---------------- MERGE SORT ----------------
void merge(vector<int>& arr, int left, int mid, int right, SortMetrics& metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        metrics.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            metrics.swaps++;
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right, SortMetrics& metrics) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid, metrics);
        mergeSort(arr, mid + 1, right, metrics);
        merge(arr, left, mid, right, metrics);
    }
}

// ---------------- QUICK SORT ----------------
int partitionArray(vector<int>& arr, int low, int high, SortMetrics& metrics) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        metrics.comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            metrics.swaps++;
        }
    }

    swap(arr[i + 1], arr[high]);
    metrics.swaps++;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, SortMetrics& metrics) {
    if (low < high) {
        int pi = partitionArray(arr, low, high, metrics);
        quickSort(arr, low, pi - 1, metrics);
        quickSort(arr, pi + 1, high, metrics);
    }
}

// ---------------- HEAP SORT ----------------
void heapify(vector<int>& arr, int n, int i, SortMetrics& metrics) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        metrics.comparisons++;
        if (arr[left] > arr[largest]) largest = left;
    }

    if (right < n) {
        metrics.comparisons++;
        if (arr[right] > arr[largest]) largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        metrics.swaps++;
        heapify(arr, n, largest, metrics);
    }
}

void heapSort(vector<int>& arr, SortMetrics& metrics) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, metrics);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        metrics.swaps++;
        heapify(arr, i, 0, metrics);
    }
}

// ---------------- COUNTING SORT ----------------
void countingSort(vector<int>& arr, SortMetrics& metrics) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);

    for (int num : arr) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
            metrics.swaps++;
        }
    }
}

// ---------------- RADIX SORT ----------------
void countingSortForRadix(vector<int>& arr, int exp, SortMetrics& metrics) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        metrics.swaps++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr, SortMetrics& metrics) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp, metrics);
    }
}

// ---------------- BUCKET SORT ----------------
void bucketSort(vector<int>& arr, SortMetrics& metrics) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int n = arr.size();

    if (maxVal == 0) return;

    vector<vector<int>> buckets(n);

    for (int num : arr) {
        int index = (num * n) / (maxVal + 1);
        buckets[index].push_back(num);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (int num : buckets[i]) {
            arr[k++] = num;
            metrics.swaps++;
        }
    }
}

// ---------------- INFO ----------------
string getStability(string algorithm) {
    if (algorithm == "Merge Sort") return "Yes";
    if (algorithm == "Quick Sort") return "No";
    if (algorithm == "Heap Sort") return "No";
    if (algorithm == "Counting Sort") return "Yes";
    if (algorithm == "Radix Sort") return "Yes";
    if (algorithm == "Bucket Sort") return "Depends";
    return "Unknown";
}

string getDescription(string algorithm) {
    if (algorithm == "Merge Sort") return "Divide and conquer stable sorting algorithm.";
    if (algorithm == "Quick Sort") return "Fast average-case sorting using pivot partition.";
    if (algorithm == "Heap Sort") return "Uses heap data structure for sorting.";
    if (algorithm == "Counting Sort") return "Counts frequency of integers and rebuilds array.";
    if (algorithm == "Radix Sort") return "Sorts numbers digit by digit.";
    if (algorithm == "Bucket Sort") return "Distributes data into buckets and sorts each bucket.";
    return "No description available.";
}