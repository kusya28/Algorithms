#include "Sorting.h"
#include <locale>

int main() {
    setlocale(LC_ALL, "Ukrainian");

    int arraySizes[] = { 100, 1000, 10000 };
    string arrayTypes[] = { "Випадковi", "Впорядкованi", "Зворотнi" };

    cout << left << setw(18) << "Тип масиву"
        << setw(8) << "Розмiр"
        << setw(22) << "Алгоритм"
        << setw(16) << "Порiвняння"
        << setw(24) << "Перестановки/Змiщення"
        << "Час (мс)" << endl;
    cout << string(105, '-') << endl;

    for (int size : arraySizes) {
        vector<vector<int>> testArrays = {
            generateRandomArray(size),
            generateSortedArray(size),
            generateReverseArray(size)
        };

        for (int typeIndex = 0; typeIndex < 3; typeIndex++) {
            SortingStats insertionStats = insertionSort(testArrays[typeIndex]);
            SortingStats selectionStats = selectionSort(testArrays[typeIndex]);
            SortingStats mergeStats = mergeSort(testArrays[typeIndex]);

            // Вставками
            cout << left << setw(18) << arrayTypes[typeIndex]
                << setw(8) << size
                << setw(22) << "Вставками"
                << setw(16) << insertionStats.comparisonsCount
                << setw(24) << insertionStats.swapsOrMovesCount
                << fixed << setprecision(3) << insertionStats.executionTimeMs << endl;

            // Вибором
            cout << left << setw(18) << ""
                << setw(8) << ""
                << setw(22) << "Вибором"
                << setw(16) << selectionStats.comparisonsCount
                << setw(24) << selectionStats.swapsOrMovesCount
                << fixed << setprecision(3) << selectionStats.executionTimeMs << endl;

            // Злиттям
            cout << left << setw(18) << ""
                << setw(8) << ""
                << setw(22) << "Злиттям"
                << setw(16) << mergeStats.comparisonsCount
                << setw(24) << mergeStats.swapsOrMovesCount
                << fixed << setprecision(3) << mergeStats.executionTimeMs << endl;

            cout << string(105, '-') << endl;
        }
    }

    return 0;
}