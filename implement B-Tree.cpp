#include <iostream>
using namespace std;

// A BTree Node
class BTreeNode {
public:
    int* keys;       // Array of keys in the node
    int t;           // Minimum degree (defines the range for the number of keys)
    BTreeNode** children; // Array of child pointers
    int n;           // Current number of keys in the node
    bool isLeaf;     // True if the node is a leaf node

    // Constructor to initialize a BTreeNode
    BTreeNode(int t, bool isLeaf);

    // Traverse the tree in-order (from smallest to largest key)
    void traverse();

    // Insert a new key into a non-full node
    void insertNonFull(int k);

    // Split a child node that is full (number of keys = 2t - 1)
    void splitChild(int i, BTreeNode* y);

    // Allow BTree to access private members of BTreeNode
    friend class BTree;
};

// A BTree class
class BTree {
public:
    BTreeNode* root; // Pointer to the root node
    int t;           // Minimum degree

    // Constructor to initialize an empty BTree
    BTree(int t) {
        root = nullptr;
        this->t = t;
    }

    // Traverse the entire tree
    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    // Insert a key into the BTree
    void insert(int k);
};

// BTreeNode constructor
BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;                      // Minimum degree
    this->isLeaf = isLeaf;            // Whether this node is a leaf
    keys = new int[2 * t - 1];        // Allocate space for keys
    children = new BTreeNode*[2 * t]; // Allocate space for child pointers
    n = 0;                            // Initialize number of keys to 0
}

// Traverse the subtree rooted at this node
void BTreeNode::traverse() {
    int i;
    // Traverse all children and keys
    for (i = 0; i < n; i++) {
        if (!isLeaf)                  // If the node is not a leaf, traverse the child before the key
            children[i]->traverse();
        cout << keys[i] << " ";       // Print the key
    }

    // Traverse the last child
    if (!isLeaf)
        children[i]->traverse();
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = n - 1; // Start from the rightmost key

    if (isLeaf) {
        // Shift keys to create space for the new key
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key into its correct position
        keys[i + 1] = k;
        n++;
    } else {
        // Find the child that will receive the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // Check if the found child is full
        if (children[i + 1]->n == 2 * t - 1) {
            // Split the child and adjust keys
            splitChild(i + 1, children[i + 1]);

            // After the split, decide which child to insert into
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Split a child node y that is full
void BTreeNode::splitChild(int i, BTreeNode* y) {
    // Create a new node z to hold (t-1) keys of y
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->n = t - 1;

    // Copy the last (t-1) keys from y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children from y to z (if not a leaf)
    if (!y->isLeaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Make space for the new child in this node
    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    // Link the new child z to this node
    children[i + 1] = z;

    // Move a key from y to this node
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++; // Increment the number of keys in this node
}

// Insert a key into the BTree
void BTree::insert(int k) {
    if (root == nullptr) {
        // If the tree is empty, create the root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert the key
        root->n = 1;       // Initialize number of keys in root to 1
    } else {
        // If the root is full, split it
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            // Make the old root a child of the new root
            s->children[0] = root;

            // Split the old root and adjust
            s->splitChild(0, root);

            // Decide which child will receive the new key
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);

            // Update the root
            root = s;
        } else {
            // Insert into the non-full root
            root->insertNonFull(k);
        }
    }
}

// Main function to demonstrate BTree functionality
int main() {
    BTree t(3); // Create a BTree with minimum degree 3

    // Insert elements
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed BTree is: ";
    t.traverse(); // Print the BTree
    cout << endl;

    return 0;
}
