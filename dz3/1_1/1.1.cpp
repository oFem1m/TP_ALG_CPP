#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void printGraph(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();
    for (int i = 0; i < verticesCount; ++i) {
        std::cout << "Vertex " << i << ": ";
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int nextVertex : nextVertices) {
            std::cout << nextVertex << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Создание графа
    const int verticesCount = 5;

    // ListGraph
    ListGraph listGraph(verticesCount);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(2, 4);

    std::cout << "ListGraph:" << std::endl;
    printGraph(listGraph);
    std::cout << std::endl;

    // Copy constructor
    ListGraph copiedListGraph(listGraph);
    std::cout << "Copied ListGraph:" << std::endl;
    printGraph(copiedListGraph);
    std::cout << std::endl;

    // MatrixGraph
    MatrixGraph matrixGraph(listGraph);
    std::cout << "MatrixGraph:" << std::endl;
    printGraph(matrixGraph);
    std::cout << std::endl;

    // SetGraph
    SetGraph setGraph(listGraph);
    std::cout << "SetGraph:" << std::endl;
    printGraph(setGraph);
    std::cout << std::endl;

    // ArcGraph
    ArcGraph arcGraph(listGraph);
    std::cout << "ArcGraph:" << std::endl;
    printGraph(arcGraph);
    std::cout << std::endl;

    return 0;
}
