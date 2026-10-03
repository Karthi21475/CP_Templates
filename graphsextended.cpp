#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
============================================================
1. 0-1 BFS
============================================================

DEFINITION:
0-1 BFS finds the shortest path from a source vertex in a
graph where every edge has weight either 0 or 1.

APPLICATIONS:
- Shortest path with edge weights only 0 and 1.
- Faster alternative to Dijkstra for 0/1 weighted graphs.

COMPLEXITY:
O(V + E)

IDEA:
- Weight 0 -> push to front of deque
- Weight 1 -> push to back of deque
============================================================
*/

vector<int> zeroOneBFS(
    int n,
    vector<vector<pair<int, int>>> &g,
    int src
) {
    const int INF = 1e9;

    vector<int> dist(n, INF);
    deque<int> dq;

    dist[src] = 0;
    dq.push_front(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                if (w == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    return dist;
}


/*
============================================================
2. TOPOLOGICAL SORT
============================================================

DEFINITION:
Topological sorting is a linear ordering of vertices of a
directed graph such that for every directed edge u -> v,
u appears before v.

APPLICATIONS:
- Prerequisites
- Dependencies
- Task scheduling
- Ordering problems

IMPORTANT:
A topological ordering exists only if the graph is a DAG
(Directed Acyclic Graph).

COMPLEXITY:
O(V + E)

METHOD:
Kahn's Algorithm using indegree.
============================================================
*/

vector<int> topologicalSort(
    int n,
    vector<vector<int>> &g
) {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : g[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);

        for (int v : g[u]) {
            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    // Cycle exists
    if ((int)order.size() != n)
        return {};

    return order;
}

/*
============================================================
4. KRUSKAL'S ALGORITHM
============================================================

DEFINITION:
Kruskal's algorithm finds a Minimum Spanning Tree (MST)
by repeatedly choosing the smallest-weight edge that does
not create a cycle.

APPLICATIONS:
- Finding Minimum Spanning Tree
- Connecting all vertices with minimum total edge cost

IDEA:
1. Sort all edges by weight.
2. Process edges from smallest to largest.
3. Add an edge if it connects two different components.
4. DSU is used to detect cycles.

COMPLEXITY:
O(E log E)

KRUSKAL IS AN MST ALGORITHM.
============================================================
*/

struct Edge {
    int u, v;
    ll w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

ll kruskal(
    int n,
    vector<Edge> edges
) {
    sort(edges.begin(), edges.end());

    DSU dsu(n);

    ll mstWeight = 0;
    int edgesUsed = 0;

    for (auto &e : edges) {

        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            edgesUsed++;

            if (edgesUsed == n - 1)
                break;
        }
    }

    return mstWeight;
}


/*
============================================================
5. MINIMUM SPANNING TREE (MST) - PRIM'S ALGORITHM
============================================================

DEFINITION:
A Minimum Spanning Tree is a spanning tree of a connected,
weighted, undirected graph with minimum possible total edge
weight.

APPLICATIONS:
- Connecting all vertices with minimum total cost.
- Network / road / cable connection problems.

PRIM'S ALGORITHM:
Starts from one vertex and repeatedly adds the minimum-weight
edge that connects the current tree to a new vertex.

COMPLEXITY:
O((V + E) log V)

KRUSKAL AND PRIM BOTH FIND AN MST.
============================================================
*/

ll prim(
    int n,
    vector<vector<pair<int, ll>>> &g
) {
    const ll INF = (1LL << 60);

    vector<bool> used(n, false);

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    ll mstWeight = 0;

    // Start from vertex 0
    pq.push({0, 0});

    while (!pq.empty()) {

        auto [w, u] = pq.top();
        pq.pop();

        if (used[u])
            continue;

        used[u] = true;
        mstWeight += w;

        for (auto [v, weight] : g[u]) {
            if (!used[v]) {
                pq.push({weight, v});
            }
        }
    }

    return mstWeight;
}



int main() {
    return 0;
}