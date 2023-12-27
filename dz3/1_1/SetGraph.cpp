#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount) : adjacencySets(verticesCount) {}

SetGraph::SetGraph(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();
    adjacencySets.resize(verticesCount);

    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int nextVertex : nextVertices) {
            AddEdge(i, nextVertex);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return static_cast<int>(adjacencySets.size());
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i = 0; i < VerticesCount(); ++i) {
        if (adjacencySets[i].count(vertex) > 0) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}
