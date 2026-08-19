#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

struct Edge { int u, v, w; };

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main() {
    ifstream fin("input/input.txt");
    ofstream fout("output/output.txt");

    int V, E;
    fin >> V >> E;

    vector<int> values, colIndex, rowPtr(1, 0);

    for (int u = 0; u < V; u++) {
        int vertex, degree;
        fin >> vertex >> degree;

        for (int j = 0; j < degree; j++) {
            int v, w;
            fin >> v >> w;
            values.push_back(w);
            colIndex.push_back(v);
        }
        rowPtr.push_back(values.size());
    }

    vector<Edge> edges;

    for (int u = 0; u < V; u++)
        for (int i = rowPtr[u]; i < rowPtr[u + 1]; i++)
            if (u < colIndex[i])
                edges.push_back({u, colIndex[i], values[i]});

    auto start = chrono::high_resolution_clock::now();

    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) { return a.w < b.w; });

    DSU dsu(V);
    long long total = 0;
    vector<Edge> mst;

    for (auto e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            total += e.w;
            if (mst.size() == V - 1) break;
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(stop - start).count();

    fout << "Kruskal MST\n";
    fout << "Edges:\n";

    for (auto e : mst)
        fout << e.u << " " << e.v << " " << e.w << "\n";

    fout << "Total Weight: " << total << "\n";
    fout << "Execution Time: " << time << " ms\n";

    fin.close();
    fout.close();

    cout << "Kruskal completed.\n";

    return 0;
}