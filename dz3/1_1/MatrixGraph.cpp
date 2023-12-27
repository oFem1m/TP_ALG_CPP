#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount) : adjacencyMatrix(verticesCount, std::vector<int>(verticesCount, 0)) {}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();
    adjacencyMatrix.resize(verticesCount, std::vector<int>(verticesCount, 0));

    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int nextVertex : nextVertices) {
            AddEdge(i, nextVertex);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(adjacencyMatrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (int i = 0; i < VerticesCount(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1) {
            nextVertices.push_back(i);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i = 0; i < VerticesCount(); ++i) {
        if (adjacencyMatrix[i][vertex] == 1) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}
