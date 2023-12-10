#include "Graph.h"
#include "TSPSolver.h"
#include <iostream>

int main() {
    for (int N = 2; N <= 10; ++N) {
        const int numExperiments = 10;
        double totalQuality = 0.0;
        double totalQualitySquared = 0.0;

        for (int i = 0; i < numExperiments; ++i) {
            Graph graph(N);
            TSPSolver solver(graph);
            double quality = solver.solve();
            totalQuality += quality;
            totalQualitySquared += quality * quality;
        }

        double meanQuality = totalQuality / numExperiments;
        double stdDevQuality = std::sqrt((totalQualitySquared / numExperiments) - (meanQuality * meanQuality));

        std::cout << "N = " << N << ": Mean Quality = " << meanQuality << ", Standard Deviation = " << stdDevQuality << std::endl;
    }

    return 0;
}
