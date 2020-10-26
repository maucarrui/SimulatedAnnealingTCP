#include <pair>

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.h"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

class Heuristic {
    private:
        Graph G;
        Solution currenSolution;
	double temperature;
	double coolingFactor;

    public:
	Hueristic(Graph G, 
		  Solution initialSolution, 
		  double initialTemperature,
		  double coolingFactor);

	std::pair<double, Solution> calculateBatch(double T, Solution s);
	void thresholdAcceptance(double T, Solution s);
	double getInitialTemperature(Solution s, double T, double P);
	double acceptedPercentage(Solution s, double T);
	double binarySearch(Solution s, double T1, double T2, double P);

	Solution getCurrentSolution();
}
