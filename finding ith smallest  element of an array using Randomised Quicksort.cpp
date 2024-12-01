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
// Rearranges the array such that elements smaller than the pivot are on the left,
// and elements greater than the pivot are on the right.
int randomizedPartition(vector<int> &arr, int low, int high) {
    // Select a random pivot index between low and high
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]); // Place the random pivot at the end for convenience

    int pivot = arr[high]; // The pivot element
    int i = low - 1; // Index of the smaller element

    // Traverse the array and compare each element with the pivot
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) { // If the current element is smaller or equal to the pivot
            i++; // Increment the index of the smaller element
            swap(arr[i], arr[j]); // Swap the smaller element into its correct position
        }
    }
    // Place the pivot in its correct sorted position
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return the index of the pivot
}

// Randomized Select algorithm
// Finds the i-th smallest element in the array without fully sorting it
int randomizedSelect(vector<int> &arr, int low, int high, int i) {
    if (low == high) { // Base case: Only one element in the array
        return arr[low];
    }

    // Partition the array and get the pivot index
    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1; // The position of the pivot in the sorted array

    // Check the position of the pivot relative to the desired element
    if (i == k) {
        return arr[pivotIndex]; // The pivot is the i-th smallest element
    } else if (i < k) {
        // If the desired element is in the left part, search in the left subarray
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else {
        // If the desired element is in the right part, search in the right subarray
        // Adjust i to reflect the new subarray's context
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

int main() {
    srand(time(0)); // Seed the random number generator with the current time

    int n; // Number of elements in the array
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n); // Array to store the elements
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i]; // Input the elements
    }

    int i; // Position of the element to find (1-based index)
    cout << "Enter the value of i (1-based index): ";
    cin >> i;

    // Check if the input index is valid
    if (i < 1 || i > n) {
        cout << "Invalid value of i. Must be between 1 and " << n << "." << endl;
        return 1; // Exit the program if the input is invalid
    }

    // Find the i-th smallest element using Randomized Select
    int ithSmallest = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << ithSmallest << endl;

    return 0; // Successful program termination
}
