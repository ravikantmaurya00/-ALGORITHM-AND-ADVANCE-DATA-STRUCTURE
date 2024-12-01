#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Class representing a node in the suffix tree
class SuffixTreeNode {
public:
    unordered_map<char, SuffixTreeNode*> children; // Map to store child nodes (keyed by characters)
    int start, *end;                              // Start and end indices of the substring represented by the edge
    int suffixIndex;                              // Index of the suffix ending at this node

    // Constructor to initialize a node
    SuffixTreeNode(int start, int* end) {
        this->start = start;
        this->end = end;
        this->suffixIndex = -1; // Initialize suffix index to -1 (not a leaf initially)
    }
};

// Class representing the Suffix Tree
class SuffixTree {
public:
    string text;               // The input string for which the suffix tree is constructed
    SuffixTreeNode* root;      // Root node of the suffix tree
    int size;                  // Length of the input string

    // Constructor to initialize the suffix tree
    SuffixTree(string s) {
        text = s;
        size = s.length();
        root = new SuffixTreeNode(-1, new int(-1)); // Root node has no substring associated
    }

    // Function to build the suffix tree
    void buildTree() {
        for (int i = 0; i < size; i++) {
            // Build the suffix tree for each suffix starting at index `i`
            buildTreeUtil(i, size - 1, i);
        }
    }

    // Utility function to insert a suffix into the tree
    void buildTreeUtil(int start, int end, int suffixIndex) {
        SuffixTreeNode* currentNode = root; // Start from the root node

        // Traverse the tree and insert characters from the suffix
        for (int i = start; i <= end; i++) {
            char currentChar = text[i]; // Current character in the suffix

            // If there is no edge for the current character, create a new node
            if (currentNode->children.find(currentChar) == currentNode->children.end()) {
                SuffixTreeNode* newNode = new SuffixTreeNode(i, new int(end));
                currentNode->children[currentChar] = newNode; // Add the new node as a child
            }

            // Move to the next node in the tree
            currentNode = currentNode->children[currentChar];
        }

        // Mark the leaf node with the suffix index
        currentNode->suffixIndex = suffixIndex;
    }

    // Function to display the suffix tree
    void display(SuffixTreeNode* node, int level) {
        if (!node) return; // Base case: if the node is null, return

        // Print indentation for the current level
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }

        // If the node represents a suffix (leaf node), print its details
        if (node->suffixIndex != -1) {
            cout << "Suffix: " << text.substr(node->start, *(node->end) - node->start + 1)
                 << ", Suffix Index: " << node->suffixIndex << endl;
        }

        // Recursively display all child nodes
        for (auto& child : node->children) {
            display(child.second, level + 1);
        }
    }
};

// Main function to demonstrate the suffix tree
int main() {
    string text;
    cout << "Enter the text: ";
    getline(cin, text); // Input the text from the user

    // Create a suffix tree
    SuffixTree suffixTree(text);
    suffixTree.buildTree();  // Build the suffix tree

    // Display the suffix tree
    cout << "\nSuffix Tree for the given text:\n";
    suffixTree.display(suffixTree.root, 0); // Display the tree starting from the root

    return 0;
}
