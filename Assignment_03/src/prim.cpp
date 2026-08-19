#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>

using namespace std;
using namespace chrono;

// ---------------------------------------------------------
// CSR Graph Structure
// ---------------------------------------------------------
struct CSRGraph
{
    int V;
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

// ---------------------------------------------------------
// Convert adjacency list to CSR
// ---------------------------------------------------------
CSRGraph convertToCSR(const vector<vector<pair<int, int>>>& adj)
{
    CSRGraph graph;

    graph.V = adj.size();

    // Build row_ptr
    graph.row_ptr.resize(graph.V + 1);

    graph.row_ptr[0] = 0;

    for (int i = 0; i < graph.V; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adj[i].size();
    }

    // Build col_idx and values
    for (int i = 0; i < graph.V; i++)
    {
        for (auto edge : adj[i])
        {
            graph.col_idx.push_back(edge.first);
            graph.values.push_back(edge.second);
        }
    }

    return graph;
}

// ---------------------------------------------------------
// Prim's Algorithm using CSR
// ---------------------------------------------------------
void primMST(const CSRGraph& graph)
{
    int V = graph.V;

    const int INF = numeric_limits<int>::max();

    // Minimum edge weight required to connect each vertex
    vector<int> key(V, INF);

    // Parent of each vertex in MST
    vector<int> parent(V, -1);

    // Check whether vertex is already included
    vector<bool> inMST(V, false);

    // Min priority queue
    // pair = {weight, vertex}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    // Start Prim's algorithm from vertex 0
    key[0] = 0;

    pq.push({0, 0});

    int edgeCount = 0;
    long long totalWeight = 0;

    // -----------------------------------------------------
    // Start timing ONLY for the algorithm
    // -----------------------------------------------------
    auto start = high_resolution_clock::now();

    while (!pq.empty())
    {
        // Get vertex with minimum key
        int u = pq.top().second;
        int weight = pq.top().first;

        pq.pop();

        // Skip if already included
        if (inMST[u])
        {
            continue;
        }

        // Add vertex to MST
        inMST[u] = true;

        // Add edge weight
        if (parent[u] != -1)
        {
            edgeCount++;
            totalWeight += weight;
        }

        // -------------------------------------------------
        // Traverse neighbours using CSR
        // -------------------------------------------------
        for (int i = graph.row_ptr[u];
             i < graph.row_ptr[u + 1];
             i++)
        {
            int v = graph.col_idx[i];
            int edgeWeight = graph.values[i];

            // If v is not in MST and this edge is cheaper
            if (!inMST[v] && edgeWeight < key[v])
            {
                key[v] = edgeWeight;
                parent[v] = u;

                pq.push({key[v], v});
            }
        }
    }

    auto stop = high_resolution_clock::now();

    double executionTime =
        duration<double, milli>(stop - start).count();

    // -----------------------------------------------------
    // Check whether graph was connected
    // -----------------------------------------------------
    if (edgeCount != V - 1)
    {
        cout << "Error: Graph is disconnected.\n";
        return;
    }

   
    cout << "\n";
    cout << "========================================\n";
    cout << "          Prim's MST\n";
    cout << "========================================\n";

    cout << "\nMST edges:\n";

    for (int v = 1; v < V; v++)
    {
        cout << parent[v]
             << " "
             << v
             << " "
             << key[v]
             << "\n";
    }

    cout << "\nTotal MST weight: "
         << totalWeight
         << "\n";

    cout << "Execution time: "
         << executionTime
         << " ms\n";
}

// ---------------------------------------------------------
// Read MST input file
// ---------------------------------------------------------
CSRGraph readGraph(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error: Cannot open input file: "
             << filename << endl;

        exit(1);
    }

    int V, E;

    file >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    // Format:
    //
    // vertex degree neighbor weight neighbor weight ...
    //
    for (int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbor;
            int weight;

            file >> neighbor >> weight;

            adj[vertex].push_back(
                {neighbor, weight}
            );
        }
    }

    file.close();

    // CSR conversion happens BEFORE Prim timing
    return convertToCSR(adj);
}

// ---------------------------------------------------------
// Main
// ---------------------------------------------------------
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage:\n";
        cout << "./prim <input_file>\n";

        return 1;
    }

    string filename = argv[1];

    // Read input and convert to CSR
    CSRGraph graph = readGraph(filename);

    // Run Prim
    primMST(graph);

    return 0;
}