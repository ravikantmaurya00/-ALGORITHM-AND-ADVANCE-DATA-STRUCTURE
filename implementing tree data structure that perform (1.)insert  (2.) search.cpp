#include <iostream>
#include <sstream>
using namespace std;

// A BTree Node
class BTreeNode {
public:
    int* keys;            // Array to store keys in the node
    BTreeNode** children; // Array of child pointers
    int t;                // Minimum degree of the BTree
    int n;                // Current number of keys in this node
    bool isLeaf;          // Indicates whether the node is a leaf

    // Constructor to initialize a node
    BTreeNode(int t, bool isLeaf);

    // Search for a key in the subtree rooted at this node
    BTreeNode* search(int k);

    // Insert a key into a non-full node
    void insertNonFull(int k);

    // Split a full child into two
    void splitChild(int i, BTreeNode* y);

    // Traverse the tree rooted at this node and print its keys
    void traverse();

    // Allow access to private members from the BTree class
    friend class BTree;
};

// BTree class
class BTree {
public:
    BTreeNode* root; // Root of the BTree
    int t;           // Minimum degree of the BTree

    // Constructor: Initializes an empty tree with minimum degree `t`
    BTree(int t) {
        root = nullptr;
        this->t = t;
    }

    // Traverse the entire tree and print its keys
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    // Search for a key in the BTree
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // Insert a single key into the tree
    void insert(int k);

    // Insert multiple keys from a space-separated string
    void insertMultiple(const string& keys);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    this->isLeaf = isLeaf;

    // Allocate space for the maximum possible number of keys and children
    keys = new int[2 * t - 1];
    children = new BTreeNode*[2 * t];
    n = 0; // Initially, there are no keys

    // Initialize keys and children to default values
    for (int i = 0; i < 2 * t - 1; i++) keys[i] = 0;
    for (int i = 0; i < 2 * t; i++) children[i] = nullptr;
}

// Search for a key in the subtree rooted at this node
BTreeNode* BTreeNode::search(int k) {
    int i = 0;

    // Find the first key that is greater than or equal to `k`
    while (i < n && k > keys[i]) i++;

    // If the key is found, return this node
    if (i < n && keys[i] == k) return this;

    // If this node is a leaf, the key is not in the tree
    if (isLeaf) return nullptr;

    // Recur to the appropriate child
    return children[i]->search(k);
}

// Traverse the BTree and print its keys in sorted order
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        // If the node is not a leaf, traverse the child before the key
        if (!isLeaf && children[i]) children[i]->traverse();
        cout << keys[i] << " "; // Print the key
    }

    // Traverse the last child, if it exists
    if (!isLeaf && children[i]) children[i]->traverse();
}

// Insert a single key into the BTree
void BTree::insert(int k) {
    if (!root) {
        // If the tree is empty, create the root and insert the key
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1; // Update the number of keys in the root
    } else {
        // If the root is full, grow the tree
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            // Make the old root a child of the new root
            s->children[0] = root;

            // Split the old root and update the new root
            s->splitChild(0, root);

            // Insert the new key into the appropriate child
            if (s->keys[0] < k) s->children[1]->insertNonFull(k);
            else s->children[0]->insertNonFull(k);

            root = s; // Update the root pointer
        } else {
            // If the root is not full, insert the key directly
            root->insertNonFull(k);
        }
    }
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (isLeaf) {
        // Find the correct position for the new key and shift keys as needed
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the key at the correct position
        keys[i + 1] = k;
        n++;
    } else {
        // Find the child that will receive the new key
        while (i >= 0 && keys[i] > k) i--;

        // If the child is full, split it
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);

            // Adjust the index if the middle key moves up
            if (keys[i + 1] < k) i++;
        }

        // Recur to the appropriate child
        children[i + 1]->insertNonFull(k);
    }
}

// Split a full child into two
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->n = t - 1; // z will have t-1 keys

    // Move the last t-1 keys of y to z
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];

    // Move the children of y to z, if applicable
    if (!y->isLeaf) {
        for (int j = 0; j < t; j++) z->children[j] = y->children[j + t];
    }

    y->n = t - 1; // Reduce the number of keys in y

    // Shift children of the current node to make space for z
    for (int j = n; j >= i + 1; j--) children[j + 1] = children[j];
    children[i + 1] = z;

    // Shift keys of the current node to make space for the middle key of y
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1]; // Move the middle key of y to the current node

    n++; // Update the key count of the current node
}

// Insert multiple keys separated by spaces
void BTree::insertMultiple(const string& keys) {
    stringstream ss(keys);
    int key;
    while (ss >> key) {
        insert(key);
    }
}

// Main function to demonstrate the program
int main() {
    BTree t(3); // BTree with minimum degree 3

    int choice;
    string input;
    while (true) {
        cout << "\n1. Insert keys\n2. Search\n3. Traverse\n4. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character

        switch (choice) {
            case 1:
                cout << "Enter keys to insert (space-separated): ";
                getline(cin, input);
                t.insertMultiple(input);
                break;
            case 2:
                int key;
                cout << "Enter key to search: ";
                cin >> key;
                if (t.search(key)) cout << "Key found\n";
                else cout << "Key not found\n";
                break;
            case 3:
                cout << "Tree traversal: ";
                t.traverse();
                cout << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
