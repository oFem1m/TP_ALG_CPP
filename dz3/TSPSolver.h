// TSPSolver.h
#pragma once
#include "Graph.h"
#include <vector>

class TSPSolver {
public:
    TSPSolver(const Graph& graph);
    double solve();
private:
    const Graph& graph;
};
