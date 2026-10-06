#include "Sorting.h"

// Сортування вставками
SortingStats insertionSort(vector<int> arrayData)
{
    SortingStats stats;
    auto startTime = chrono::high_resolution_clock::now();

    int size = arrayData.size();
    for (int i = 1; i < size; i++) {
        int key = arrayData[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisonsCount++;
            if (arrayData[j] > key) {
                arrayData[j + 1] = arrayData[j];
                stats.swapsOrMovesCount++;
                j--;
            }
            else {
                break;
            }
        }
        arrayData[j + 1] = key;
    }

    auto endTime = chrono::high_resolution_clock::now();
    stats.executionTimeMs = chrono::duration<double, milli>(endTime - startTime).count();
    return stats;
}

// Сортування вибором
SortingStats selectionSort(vector<int> arrayData) {
    SortingStats stats;
    auto startTime = chrono::high_resolution_clock::now();

    int size = arrayData.size();
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            stats.comparisonsCount++;
            if (arrayData[j] < arrayData[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arrayData[i];
            arrayData[i] = arrayData[minIndex];
            arrayData[minIndex] = temp;
            stats.swapsOrMovesCount++;
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    stats.executionTimeMs = chrono::duration<double, milli>(endTime - startTime).count();
    return stats;
}

// Сортування злиттям + допоміжні функції
void merge(vector<int>& arrayData, int left, int mid, int right, SortingStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftSubarray(n1);
    vector<int> rightSubarray(n2);

    for (int i = 0; i < n1; i++) leftSubarray[i] = arrayData[left + i];
    for (int j = 0; j < n2; j++) rightSubarray[j] = arrayData[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        stats.comparisonsCount++;
        if (leftSubarray[i] <= rightSubarray[j]) {
            arrayData[k] = leftSubarray[i];
            i++;
        }
        else {
            arrayData[k] = rightSubarray[j];
            j++;
        }
        stats.swapsOrMovesCount++;
        k++;
    }

    while (i < n1) {
        arrayData[k] = leftSubarray[i];
        i++;
        k++;
        stats.swapsOrMovesCount++;
    }

    while (j < n2) {
        arrayData[k] = rightSubarray[j];
        j++;
        k++;
        stats.swapsOrMovesCount++;
    }
}

void mergeSortRecursive(vector<int>& arrayData, int left, int right, SortingStats& stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arrayData, left, mid, stats);
        mergeSortRecursive(arrayData, mid + 1, right, stats);
        merge(arrayData, left, mid, right, stats);
    }
}

SortingStats mergeSort(vector<int> arrayData) {
    SortingStats stats;
    auto startTime = chrono::high_resolution_clock::now();

    if (!arrayData.empty()) {
        mergeSortRecursive(arrayData, 0, arrayData.size() - 1, stats);
    }

    auto endTime = chrono::high_resolution_clock::now();
    stats.executionTimeMs = chrono::duration<double, milli>(endTime - startTime).count();
    return stats;
}

// Генератор рандомних масивів
vector<int> generateRandomArray(int size) {
    vector<int> arrayData(size);
    mt19937 generator(42);
    uniform_int_distribution<int> distribution(1, 100000);
    for (int i = 0; i < size; i++) {
        arrayData[i] = distribution(generator);
    }
    return arrayData;
}

// Генератор впорядкованих масивів
vector<int> generateSortedArray(int size) {
    vector<int> arrayData(size);
    for (int i = 0; i < size; i++) {
        arrayData[i] = i;
    }
    return arrayData;
}

// Генератор зворотних масивів
vector<int> generateReverseArray(int size) {
    vector<int> arrayData(size);
    for (int i = 0; i < size; i++) {
        arrayData[i] = size - i;
    }
    return arrayData;
}