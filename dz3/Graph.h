// Graph.h
#pragma once
#include <vector>
#include <cmath>

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

class Graph {
public:
    Graph(int n);
    double distance(int i, int j) const;
    int size() const;
private:
    std::vector<Point> points;
};
