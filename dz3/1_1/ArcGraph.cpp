#include "ArcGraph.h"

ArcGraph::ArcGraph(int verticesCount) {}

ArcGraph::ArcGraph(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();

    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int nextVertex : nextVertices) {
            AddEdge(i, nextVertex);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    // Находим максимальный номер вершины среди всех рёбер
    int maxVertex = 0;
    for (const auto& edge : edges) {
        maxVertex = std::max(maxVertex, std::max(edge.first, edge.second));
    }
    return maxVertex + 1;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (const auto& edge : edges) {
        if (edge.first == vertex) {
            nextVertices.push_back(edge.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (const auto& edge : edges) {
        if (edge.second == vertex) {
            prevVertices.push_back(edge.first);
        }
    }
    return prevVertices;
}
