#include "dataset_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool loadCSV(const string& filename, vector<string>& labels, vector<int>& values) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string label, valueStr;

        getline(ss, label, ',');
        getline(ss, valueStr, ',');

        labels.push_back(label);
        values.push_back(stoi(valueStr));
    }

    file.close();
    return true;
}

void displayDataset(const vector<string>& labels, const vector<int>& values) {
    cout << "\nOriginal Dataset:\n";
    for (int i = 0; i < labels.size(); i++) {
        cout << labels[i] << " - " << values[i] << endl;
    }
}

void displaySortedDataset(const vector<string>& labels, const vector<int>& values) {
    cout << "\nSorted Dataset:\n";
    for (int i = 0; i < labels.size(); i++) {
        cout << labels[i] << " - " << values[i] << endl;
    }
}