#include "Hueristic.h"

Heurisic::Heuristic(Graph G, Solution initialSolution, 
		    double initialTemperature, double coolingFactor) {
    this->G                = G;
    this->currentSolution  = initialSolution;
    this->temperature      = initialTemperature;
    this->coolingFactor    = coolingFactor;
}

std::pair<double, Solution> Heuristic::calculateBatch(double T, Solution s) {
    return std::make_pair(T, s);
}

void Hueristic::thresholdAcceptance(double T, Solution s) {
    return;
}

double Hueristic::getInitialTemperature(Solution s, double T, double P) {
    return T;
}

double Heuristic::acceptedPercentage(Solution s, double T) {
    return T;
}

double Heuristic::binarySearch(Solution s, double T1, double T2, double P) {
    return T1;
}

Solution Heuristic::getCurrentSolution {
    return currentSolution;
}
