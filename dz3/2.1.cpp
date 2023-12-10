#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами.
*/

const int INF = 1e9 + 7;

struct Edge {
    int to, weight;
};

void dijkstra(const vector<vector<Edge>>& graph, vector<int>& distance, vector<int>& count, int start) {
    int n = int(graph.size());
    distance.assign(n, INF);
    count.assign(n, 0);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distance[start] = 0;
    count[start] = 1;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > distance[u]) {
            continue;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                count[v] = count[u];
                pq.emplace(distance[v], v);
            } else if (distance[u] + weight == distance[v]) {
                count[v] += count[u];
            }
        }
    }
}

int main() {
    int v, n;
    cin >> v >> n;

    vector<vector<Edge>> graph(v);

    for (int i = 0; i < n; ++i) {
        int u, w;
        cin >> u >> w;
        graph[u].push_back({w, 1});
        graph[w].push_back({u, 1});
    }

    int u, w;
    cin >> u >> w;

    vector<int> distance, count;
    dijkstra(graph, distance, count, u);

    cout << count[w] << endl;

    return 0;
}
