#include <iostream>
#include <vector>
#include <algorithm> // for sort()

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight; // Source vertex, destination vertex, and weight of the edge
};

// Function to compare two edges based on their weights
// Used for sorting edges in ascending order of weight
bool compareEdges(const Edge &e1, const Edge &e2) {
    return e1.weight < e2.weight;
}

// Disjoint Set (Union-Find) Structure
// Helps efficiently manage connected components in the graph
class DisjointSet {
private:
    vector<int> parent, rank; // `parent` stores the parent of each node, `rank` is used to optimize unions

public:
    // Constructor: initialize parent and rank arrays
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0); // Initially, all ranks are 0
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Each node is its own parent initially
        }
    }

    // Find the root of the set containing 'u' with path compression
    int find(int u) {
        if (u != parent[u]) { // If 'u' is not its own parent, recursively find its root
            parent[u] = find(parent[u]); // Path compression: flatten the tree
        }
        return parent[u];
    }

    // Union two sets based on rank
    void unionSets(int u, int v) {
        int rootU = find(u); // Find the root of the set containing 'u'
        int rootV = find(v); // Find the root of the set containing 'v'

        if (rootU != rootV) { // Only union if they are in different sets
            if (rank[rootU] < rank[rootV]) { // Attach the smaller tree under the larger tree
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else { // If ranks are equal, arbitrarily choose one as root and increment its rank
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Kruskal's algorithm to find the Minimum Spanning Tree (MST)
void kruskalMST(int V, vector<Edge> &edges) {
    // Sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(V); // Initialize disjoint set for the vertices

    vector<Edge> mst; // To store the edges included in the MST
    int mstWeight = 0; // To store the total weight of the MST

    for (const auto &edge : edges) {
        // Find the roots of the source and destination vertices of the current edge
        int rootSrc = ds.find(edge.src);
        int rootDest = ds.find(edge.dest);

        // If including this edge doesn't form a cycle
        if (rootSrc != rootDest) {
            mst.push_back(edge); // Include the edge in the MST
            mstWeight += edge.weight; // Add the weight of the edge to the total MST weight
            ds.unionSets(rootSrc, rootDest); // Union the two sets
        }
    }

    // Print the edges of the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    // Print the total weight of the MST
    cout << "Total weight of the MST: " << mstWeight << endl;
}

int main() {
    int V, E; // Number of vertices and edges in the graph
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E); // Array to store the edges
    cout << "Enter the edges (source, destination, weight):\n";
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight; // Input each edge
    }

    // Find and print the Minimum Spanning Tree
    kruskalMST(V, edges);

    return 0; // Program ends successfully
}
