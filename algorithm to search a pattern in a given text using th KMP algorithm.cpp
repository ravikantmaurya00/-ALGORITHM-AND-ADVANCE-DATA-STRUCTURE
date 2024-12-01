#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to build the LPS (Longest Prefix Suffix) array for the pattern
void buildLPSArray(const string& pattern, vector<int>& lps) {
    int m = pattern.length(); // Length of the pattern
    int length = 0;          // Length of the previous longest prefix suffix
    lps[0] = 0;              // LPS[0] is always 0
    int i = 1;               // Start from the second character of the pattern

    // Compute LPS array values for pattern[1...m-1]
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            // If current character matches the character at the end of the current prefix
            length++;
            lps[i] = length; // Store the length of the current prefix suffix
            i++;
        } else {
            // If the characters do not match
            if (length != 0) {
                // Try the previous longest prefix suffix
                length = lps[length - 1];
            } else {
                // If no prefix suffix is found, set LPS[i] to 0
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP pattern searching algorithm
void KMPSearch(const string& text, const string& pattern) {
    int n = text.length(); // Length of the text
    int m = pattern.length(); // Length of the pattern
    vector<int> lps(m); // LPS array to hold the longest prefix suffix values for the pattern

    // Build the LPS array for the pattern
    buildLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    // Loop through the text to find occurrences of the pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            // If characters match, move both indices forward
            i++;
            j++;
        }

        // If the entire pattern is found
        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1]; // Get the next position to check in the pattern
        }
        // If there is a mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                // Skip the matched part of the pattern and try again
                j = lps[j - 1];
            } else {
                // If no match, move the text index forward
                i++;
            }
        }
    }
}

// Main function to demonstrate the KMP algorithm
int main() {
    string text, pattern;

    // Input text and pattern from the user
    cout << "Enter the text: ";
    getline(cin, text); // Get the full text input
    cout << "Enter the pattern to search for: ";
    getline(cin, pattern); // Get the pattern input

    // Display the input text and pattern
    cout << "\nText: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    // Call KMPSearch to search for the pattern in the text
    KMPSearch(text, pattern);

    return 0;
}
