#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/*
Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога,
которая возвращается в этот же город.
Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

Формат ввода
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Все указанные дороги двусторонние. Между любыми двумя городами может быть больше одной дороги.
Последняя строка содержит маршрут (откуда и куда нужно доехать).

Формат вывода
Вывести длину самого короткого маршрута.
*/

const int INF = INT_MAX;

struct Edge {
    int to;
    int weight;
};

void Dijkstra(const vector<vector<Edge>>& graph, int start, vector<int>& distances) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);
    distances[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > distances[u]) {
            continue;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.emplace(distances[v], v);
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N);

    for (int i = 0; i < M; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;

        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight});
    }

    int start, destination;
    cin >> start >> destination;

    vector<int> distances(N, INF);
    Dijkstra(graph, start, distances);

    cout << distances[destination] << endl;

    return 0;
}
