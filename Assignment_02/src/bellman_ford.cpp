#include <algorithm>
#include <fstream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
constexpr ll INF = (1LL << 60);

struct CSRGraph {
    int n;
    vector<int> offset, to;
    vector<ll> weight;
};

CSRGraph buildCSR(int n, const vector<tuple<int, int, ll>>& edges) {
    CSRGraph graph{n, vector<int>(n + 1, 0), {}, {}};
    for (auto [u, v, w] : edges) graph.offset[u + 1]++;
    for (int i = 1; i <= n; ++i) graph.offset[i] += graph.offset[i - 1];

    graph.to.resize(edges.size());
    graph.weight.resize(edges.size());
    vector<int> next = graph.offset;
    for (auto [u, v, w] : edges) {
        int index = next[u]++;
        graph.to[index] = v;
        graph.weight[index] = w;
    }
    return graph;
}

pair<vector<ll>, bool> bellmanFord(const CSRGraph& graph, int source) {
    vector<ll> dist(graph.n, INF);
    dist[source] = 0;

    for (int pass = 1; pass < graph.n; ++pass) {
        bool changed = false;
        for (int u = 0; u < graph.n; ++u) {
            if (dist[u] == INF) continue;
            for (int e = graph.offset[u]; e < graph.offset[u + 1]; ++e) {
                int v = graph.to[e];
                if (dist[u] + graph.weight[e] < dist[v]) {
                    dist[v] = dist[u] + graph.weight[e];
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    for (int u = 0; u < graph.n; ++u) {
        if (dist[u] == INF) continue;
        for (int e = graph.offset[u]; e < graph.offset[u + 1]; ++e) {
            if (dist[u] + graph.weight[e] < dist[graph.to[e]]) {
                return {dist, true};
            }
        }
    }
    return {dist, false};
}

int main() {
    ifstream in("../input/input_bellman.txt");
    ofstream out("../output/bellman_ford_output.txt");

    int n, m, source;
    if (!(in >> n >> m >> source)) return 1;

    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        in >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    auto [dist, negativeCycle] = bellmanFord(buildCSR(n, edges), source);
    if (negativeCycle) {
        out << "Reachable negative cycle detected\n";
    } else {
        for (int v = 0; v < n; ++v) {
            out << source << " -> " << v << " = ";
            if (dist[v] == INF) out << "INF\n";
            else out << dist[v] << '\n';
        }
    }
}
