#include "TSPSolver.h"
#include <vector>
#include <limits>
#include <iostream>

TSPSolver::TSPSolver(const Graph& graph) : graph(graph) {}

double TSPSolver::solve() {
    int n = graph.points.size();
    std::vector<bool> visited(n, false);
    visited[0] = true;

    double totalDistance = 0.0;

    for (int i = 1; i < n; ++i) {
        int u = -1;
        int v = -1;
        double minDistance = std::numeric_limits<double>::infinity();

        for (int j = 0; j < n; ++j) {
            if (visited[j]) {
                for (int k = 0; k < n; ++k) {
                    if (!visited[k] && graph.distance(j, k) < minDistance) {
                        minDistance = graph.distance(j, k);
                        u = j;
                        v = k;
                    }
                }
            }
        }

        visited[v] = true;
        totalDistance += minDistance;
    }

    totalDistance += graph.distance(n - 1, 0);

    return totalDistance;
}
