#include <utility>
#include <string>
#include <limits>
#include <cmath>

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
	double temperature;
	double coolingFactor;
        double L;
        double epsilon;
        double epsilon_p;

        Solution initialSolution;
        Solution currentSolution;
        Solution bestSolution;

        std::string status;
        std::string getStatus();

    public:
	Heuristic(Graph G, 
		  Solution initialSolution, 
		  double initialTemperature,
		  double coolingFactor,
		  double L,
		  double epislon,
		  double epsilon_p);

	double calculateBatch(double T);
	void thresholdAcceptance();
	void getInitialTemperature(double P);
	double acceptedPercentage(Solution s, double T);
	double binarySearch(Solution s, double T1, double T2, double P);

	Solution getCurrentSolution();
        Solution getBestSolution();
        
        std::string printBestSolution();
        std::string printStatus();
};
