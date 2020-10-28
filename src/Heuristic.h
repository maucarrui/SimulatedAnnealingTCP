#include <utility>
#include <limits>

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
        Solution currentSolution;
	double temperature;
	double coolingFactor;
        double L;
        double epsilon;
        double epsilon_p;

    public:
	Heuristic(Graph G, 
		  Solution initialSolution, 
		  double initialTemperature,
		  double coolingFactor,
		  double L,
		  double epislon,
		  double epsilon_p);

	std::pair<double, Solution> calculateBatch(double T, Solution s);
	void thresholdAcceptance();
	double getInitialTemperature(Solution s, double T, double P);
	double acceptedPercentage(Solution s, double T);
	double binarySearch(Solution s, double T1, double T2, double P);

	Solution getCurrentSolution();
};
