#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <string>
using namespace std;

struct SortMetrics {
    long long comparisons = 0;
    long long swaps = 0;
};

void mergeSort(vector<int>& arr, int left, int right, SortMetrics& metrics);
void quickSort(vector<int>& arr, int low, int high, SortMetrics& metrics);
void heapSort(vector<int>& arr, SortMetrics& metrics);
void countingSort(vector<int>& arr, SortMetrics& metrics);
void radixSort(vector<int>& arr, SortMetrics& metrics);
void bucketSort(vector<int>& arr, SortMetrics& metrics);

string getStability(string algorithm);
string getDescription(string algorithm);

#endif