#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for srand()

using namespace std;

// Function to swap two elements in the array
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function with a randomized pivot
// It rearranges the array such that elements smaller than the pivot
// are on the left, and elements greater than the pivot are on the right
int randomizedPartition(vector<int> &arr, int low, int high, int &comparisonCount) {
    // Select a random pivot index within the range [low, high]
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]); // Place the random pivot at the end for convenience

    int pivot = arr[high]; // The pivot element
    int i = low - 1; // Index of the smaller element

    // Traverse the array and compare each element with the pivot
    for (int j = low; j < high; ++j) {
        comparisonCount++; // Increment the comparison counter
        if (arr[j] <= pivot) {
            i++; // Move the boundary of smaller elements
            swap(arr[i], arr[j]); // Place the smaller element in the correct position
        }
    }
    // Place the pivot in its correct sorted position
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return the index of the pivot
}

// Randomized Quick Sort
// A divide-and-conquer algorithm that recursively sorts subarrays
void randomizedQuickSort(vector<int> &arr, int low, int high, int &comparisonCount) {
    if (low < high) { // Base condition for recursion
        // Partition the array and get the pivot index
        int pivotIndex = randomizedPartition(arr, low, high, comparisonCount);

        // Recursively sort the subarray before the pivot
        randomizedQuickSort(arr, low, pivotIndex - 1, comparisonCount);

        // Recursively sort the subarray after the pivot
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisonCount);
    }
}

int main() {
    srand(time(0)); // Seed the random number generator with the current time

    int n; // Number of elements in the array
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n); // Initialize a vector to hold the elements
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i]; // Input the elements
    }

    int comparisonCount = 0; // Initialize the comparison counter

    // Sort the array using randomized quicksort
    randomizedQuickSort(arr, 0, n - 1, comparisonCount);

    // Output the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " "; // Print each element of the sorted array
    }
    cout << endl;

    // Output the number of comparisons made during sorting
    cout << "Number of comparisons: " << comparisonCount << endl;

    return 0; // Indicate successful program termination
}
