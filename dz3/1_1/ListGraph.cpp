#include "ListGraph.h"

ListGraph::ListGraph(int verticesCount) : adjacencyLists(verticesCount) {}

ListGraph::ListGraph(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();
    adjacencyLists.resize(verticesCount);

    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int nextVertex : nextVertices) {
            AddEdge(i, nextVertex);
        }
    }
}

void ListGraph::AddEdge(int from, int to) {
    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return static_cast<int>(adjacencyLists.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i = 0; i < VerticesCount(); ++i) {
        for (int nextVertex : adjacencyLists[i]) {
            if (nextVertex == vertex) {
                prevVertices.push_back(i);
            }
        }
    }
    return prevVertices;
}
