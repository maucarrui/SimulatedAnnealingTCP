#include "Heuristic.h"

Heuristic::Heuristic(Graph G, Solution initialSolution, 
		    double initialTemperature, double coolingFactor,
		    double L, double epsilon, double epsilon_p) {
    this->G                = G;
    this->L                = L;
    this->initialSolution  = initialSolution;
    this->currentSolution  = initialSolution;
    this->temperature      = initialTemperature;
    this->coolingFactor    = coolingFactor;
    this->epsilon          = epsilon;
    this->epsilon_p        = epsilon_p;

    this->bestSolution.setCost(std::numeric_limits<double>::infinity());
}

std::string Heuristic::getStatus() {
    std::string temp;
    temp  = "-----------\n";
    temp += "(T: " + std::to_string(temperature) + ", ";
    temp += "Cost: " + std::to_string(currentSolution.getCost()) + ")\n";
    temp += currentSolution.toString() + "\n";
    return temp;
}

double Heuristic::calculateBatch(double T) {
    int c = 0, d = 0;
    double r = 0.0;
    double currentCost, newCost, minCost;
    std::vector<int> minSequence;
    std::pair<double, std::vector<int>> ps;

    int maxTries = L * 3;

    while ( (c < L) && (d < maxTries) ) {
        ps = currentSolution.getRandomNeighbor(G);

	currentCost = currentSolution.getCost();
	newCost     = ps.first;

	if (newCost <= currentCost + T) {
	    // Update the current solution.
	    currentSolution.setCost(newCost);
	    currentSolution.setSequence(ps.second);
	  
	    // Check if the new solution is a minimum.
            minCost = bestSolution.getCost();

	    if (newCost <= minCost) {
	        minSequence = currentSolution.getSequence();
		bestSolution.setSequence(minSequence);
		bestSolution.setCost(newCost);
	    }

	    c++;
	    r += newCost;
	} else {
	    d++;
	}
    }
    
    return (r / L);
}

void Heuristic::thresholdAcceptance() {
    double p = 0.0, q = 0.0;
    
    while (temperature > epsilon) {
        q = std::numeric_limits<double>::infinity();
	
	while (p <= q) { 
	    q = p;
	    p = calculateBatch(temperature);
	}

	status += getStatus();

	temperature *= coolingFactor;
    }

}

void Heuristic::getInitialTemperature(double P) {
    double T1, T2;
    Solution s = currentSolution;
    double   T = temperature;
    double   p = acceptedPercentage(s, T);

    if (std::abs((P - p)) <= epsilon_p) {
        return;
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

    this->temperature = binarySearch(s, T1, T2, P);
}

double Heuristic::acceptedPercentage(Solution s, double T) {
    double c = 0.0;
    Solution newSolution;
    Solution current = s;
    std::pair<double, std::vector<int>> ps;

    double currentCost, newCost;
    
    for (int i = 0; i < L; i++) {
        ps = current.getRandomNeighbor(G);

	currentCost = current.getCost();
	newCost     = ps.first;
	
	if (newCost <= currentCost + T) {
	    // Update the current solution
	    current.setCost(newCost);
	    current.setSequence(ps.second);
	    c++;
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

std::string Heuristic::printBestSolution() {
    std::string temp;
    temp += "===== BEST SOLUTION =====\n";
    temp += bestSolution.toString() + "\n";
    temp += "Best cost: " + std::to_string(bestSolution.getCost()) + "\n";
    return temp;
}

std::string Heuristic::printStatus() {
    std::string temp;
    temp += status;
    temp += "\n ---------- \n";
    temp += printBestSolution();
    return temp;
}
