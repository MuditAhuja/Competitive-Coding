#ifndef DATASET_UTILS_H
#define DATASET_UTILS_H

#include <vector>
#include <string>
using namespace std;

bool loadCSV(const string& filename, vector<string>& labels, vector<int>& values);
void displayDataset(const vector<string>& labels, const vector<int>& values);
void displaySortedDataset(const vector<string>& labels, const vector<int>& values);

#endif