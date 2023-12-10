// Graph.cpp
#include "Graph.h"
#include <random>

Graph::Graph(int n) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);
        points.push_back(Point(x, y));
    }
}

double Graph::distance(int i, int j) const {
    double dx = points[i].x - points[j].x;
    double dy = points[i].y - points[j].y;
    return std::sqrt(dx * dx + dy * dy);
}

int Graph::size() const {
    return points.size();
}
