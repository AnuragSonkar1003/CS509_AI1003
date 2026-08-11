#include <algorithm>
#include <fstream>
#include <tuple>
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

vector<vector<ll>> floydWarshall(const CSRGraph& graph, bool& negativeCycle) {
    vector<vector<ll>> dist(graph.n, vector<ll>(graph.n, INF));

    for (int u = 0; u < graph.n; ++u) {
        dist[u][u] = 0;
        for (int e = graph.offset[u]; e < graph.offset[u + 1]; ++e) {
            dist[u][graph.to[e]] = min(dist[u][graph.to[e]], graph.weight[e]);
        }
    }

    for (int k = 0; k < graph.n; ++k)
        for (int i = 0; i < graph.n; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < graph.n; ++j) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }

    negativeCycle = false;
    for (int v = 0; v < graph.n; ++v)
        if (dist[v][v] < 0) negativeCycle = true;
    return dist;
}

int main() {
    ifstream in("../input/input_floyd.txt");
    ofstream out("../output/floyd_output.txt");

    // Source is retained only so both programs share the same input format.
    int n, m, unusedSource;
    if (!(in >> n >> m >> unusedSource)) return 1;

    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        in >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    bool negativeCycle;
    auto dist = floydWarshall(buildCSR(n, edges), negativeCycle);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) out << "INF";
            else out << dist[i][j];
            out << (j + 1 == n ? '\n' : ' ');
        }
    }
    if (negativeCycle) out << "Negative cycle detected\n";
}
