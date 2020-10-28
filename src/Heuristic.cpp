#include "Heuristic.h"

Heuristic::Heuristic(Graph G, Solution initialSolution, 
		    double initialTemperature, double coolingFactor,
		    double L, double epsilon, double epsilon_p) {
    this->G                = G;
    this->L                = L;
    this->currentSolution  = initialSolution;
    this->temperature      = initialTemperature;
    this->coolingFactor    = coolingFactor;
    this->epsilon          = epsilon;
    this->epsilon_p        = epsilon_p;
}

std::pair<double, Solution> Heuristic::calculateBatch(double T, Solution s) {
    int c    = 0;
    double r = 0.0;
    Solution current = s;
    Solution neighbor;
    double currentCost, newCost;
    
    while (c < L) {
        neighbor    = s.getRandomNeighbor();
	currentCost = G.getCost(current);
	newCost     = G.getCost(neighbor);

	if (newCost <= currentCost + T) {
	    current = neighbor;
	    c++;
	    r += newCost;
	}
    }
    
    return std::make_pair((r / L), current);
}

void Heuristic::thresholdAcceptance() {
    double p = 0.0, q = 0.0;
    std::pair<double, Solution> ps;
    
    while (temperature > epsilon) {
        q = std::numeric_limits<double>::infinity();
	
	while (p <= q) { 
	    q = p;
	    ps = calculateBatch(temperature, currentSolution);
	    q = ps.first;
	    currentSolution = ps.second;
	}

	temperature *= coolingFactor;
    }

}

double Heuristic::getInitialTemperature(Solution s, double T, double P) {
    double T1, T2;
    double p = acceptedPercentage(s, T);

    if (std::abs((P - p)) <= epsilon_p) {
        return T;
    }
    
    if (p < P) {

        while (p < P) {
	    T = 2 * T;
	    p = acceptedPercentage(s, T);
	}

	T1 = T / 2;
	T2 = T;

    } else {

        while (p > P) {
	    T = T / 2;
	    p = acceptedPercentage(s, T);
	}
	
	T1 = T;
	T2 = 2 * T;

    }

    return binarySearch(s, T1, T2, P);
}

double Heuristic::acceptedPercentage(Solution s, double T) {
    double c = 0.0;
    Solution newSolution;
    Solution current = s;

    double currentCost, newCost;
    
    for (int i = 0; i < L; i++) {
        newSolution = current.getRandomNeighbor();
	currentCost = G.getCost(current);
	newCost     = G.getCost(newSolution);
	
	if (newCost <= currentCost + T) {
	    c++;
	    current = newSolution;
	}
    }

    return c / L;
}

double Heuristic::binarySearch(Solution s, double T1, double T2, double P) {
    double Tm = (T1 + T2) / 2;
    
    if ( (T2 - T1) < epsilon_p )
        return Tm;
    
    double p = acceptedPercentage(s, Tm);

    if (std::abs((P-p)) < epsilon_p)
      return Tm;

    if (p > P)
      return binarySearch(s, T1, Tm, P);
    else
      return binarySearch(s, Tm, T2, P);
    
    return T1;
}

Solution Heuristic::getCurrentSolution() {
    return currentSolution;
}