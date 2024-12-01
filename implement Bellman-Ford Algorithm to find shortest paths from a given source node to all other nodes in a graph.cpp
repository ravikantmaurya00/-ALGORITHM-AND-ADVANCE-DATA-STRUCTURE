#include <iostream>
#include <vector>
#include <climits> // For INT_MAX to represent infinity

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight; // Source vertex, destination vertex, and weight of the edge
};

// Bellman-Ford Algorithm
void bellmanFord(int V, int E, vector<Edge> &edges, int source) {
    // Initialize distances to all vertices as infinity (INT_MAX)
    vector<int> distance(V, INT_MAX);
    distance[source] = 0; // Distance to the source vertex is 0

    // **Relaxation Phase**
    // Relax all edges |V| - 1 times (where |V| is the number of vertices)
    for (int i = 1; i <= V - 1; ++i) {
        for (const auto &edge : edges) {
            int u = edge.src;    // Source vertex of the edge
            int v = edge.dest;  // Destination vertex of the edge
            int weight = edge.weight; // Weight of the edge

            // If the current distance to 'u' is not infinity and we find a shorter path to 'v'
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight; // Update the distance to 'v'
            }
        }
    }

    // **Negative-Weight Cycle Detection**
    // Check all edges one more time to detect negative-weight cycles
    for (const auto &edge : edges) {
        int u = edge.src;    // Source vertex of the edge
        int v = edge.dest;  // Destination vertex of the edge
        int weight = edge.weight; // Weight of the edge

        // If we can still find a shorter path, a negative-weight cycle exists
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle." << endl;
            return; // Terminate the function if a cycle is found
        }
    }

    // **Output the Shortest Distances**
    cout << "Vertex Distance from Source (" << source << "):" << endl;
    for (int i = 0; i < V; ++i) {
        if (distance[i] == INT_MAX) {
            cout << i << ": INF" << endl; // If a vertex is unreachable, its distance is "INF"
        } else {
            cout << i << ": " << distance[i] << endl; // Print the shortest distance to the vertex
        }
    }
}

int main() {
    int V, E, source; // Number of vertices, edges, and the source vertex
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E); // Array to store the edges
    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight; // Input each edge
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source); // Run the Bellman-Ford algorithm

    return 0; // Program ends successfully
}
