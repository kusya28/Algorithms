#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>

using namespace std;

struct SortingStats {
    long long comparisonsCount = 0;
    long long swapsOrMovesCount = 0;
    double executionTimeMs = 0.0;
};

// Прототипи функцій сортування
SortingStats insertionSort(vector<int>);
SortingStats selectionSort(vector<int>);
SortingStats mergeSort(vector<int>);

// Прототипи генераторів масивів
vector<int> generateRandomArray(int);
vector<int> generateSortedArray(int);
vector<int> generateReverseArray(int);