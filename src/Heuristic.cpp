#include "Heuristic.h"

/**
 * Constructor for the Simulated Annealing Heuristic to 
 * find optimal solutions for the TSP.
 * For this heuristic to work is neccesary to have the 
 * graph representing the cities, an initial solution,
 * an initial temperature, a cooling factor, the 
 * amount of solutions that will be generated in each 
 * step (L), and epsilons to tell when the heuristic 
 * needs to stop and when the temperature is good enough.
 *
 * @param G                  The graph.
 * @param initialSolution    The initial solution.
 * @param initialTemperature The initial temperature.
 * @param coolingFactor      The cooling factor.
 * @param L                  The amount of solutions for each batch.
 * @param epsilon            Epsilon to tell when to stop the heuristic.
 * @param epsilon_p          Epsilon to tell when a temperature is good enough.
 */
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

/**
 * Returns a string representation of the status of the heuristic.
 * The status of an heuristic consists of all the temperatures the 
 * heuristic has gone through and its current cost in each temperature.
 *
 * @return The string representation of the status of the heuristic.
 */
std::string Heuristic::getStatus() {
    std::string temp;
    temp  = "-----------\n";
    temp += "(T: " + std::to_string(temperature) + ", ";
    temp += "Cost: " + std::to_string(currentSolution.getCost()) + ")\n";
    temp += currentSolution.toString() + "\n";
    return temp;
}

/**
 * Sweeps a given solution and returns the local minimum found.
 * Sweeping a solution consists of hill descending its search space
 * by checking all the neighbors of the solution and checking if 
 * one of those has a lower cost than the given one, repeating 
 * this process until the solution is a minimum.
 *
 * @param s The solution to sweep.
 * @return  A local minimum solution.
 */
Solution Heuristic::sweepSolution(Solution s) {
    bool foundBetter = true;
    Solution current = s;
    Solution minimum = s;
    std::vector<int>::iterator it, jt;
    std::vector<int> seq;
    double currentCost, minCost, newCost;
    int i, j;
    int n = s.getSequence().size();

    while (foundBetter) {
        foundBetter = false;
        currentCost = current.getCost();
	seq         = current.getSequence();

	for (i = 0; i <= n - 2; i++) {
	    j = i + 1;

	    for (j = i + 1; j <= n-1; j++) {
	          minCost = minimum.getCost();
		  newCost = G.getSwappedCost(i, j, currentCost, seq);
		  
		  if (newCost < minCost) {
		      // Swap elements in the current sequence.
		      std::vector<int> newSeq = seq;
		      int temp = newSeq[i];
		      newSeq[i] = newSeq[j];
		      newSeq[j] = temp;

		      minimum.setSequence(newSeq);
		      minimum.setCost(newCost);
		      
		      foundBetter = true;
		  }
	    }
	}

	if (foundBetter)
	    current = minimum;
    }

    return current;
}

/**
 * Given a temperature, it calculates a batch of solutions.
 * Keeping the best solution in the batch while also updating
 * the minimal solution that has been found, and in the 
 * end it returns the average number of solutions that were 
 * accepted in the batch.
 *
 * @param  The temperature.
 * @return The average number of solutions that were accepted in the batch.
 */
double Heuristic::calculateBatch(double T) {
    int c = 0, d = 0;
    int si, sj;
    double r = 0.0;
    double currentCost, newCost, minCost;
    std::vector<int> currentSeq, newSeq;
    
    std::pair<std::pair<int, int>, std::vector<int>> neighborData;
    std::pair<int, int> swapped;

    int maxTries = L * 3;

    while ( (c < L) && (d < maxTries) ) {
        neighborData = currentSolution.getRandomNeighbor();
	swapped      = neighborData.first;
	newSeq       = neighborData.second;

        si = swapped.first;
	sj = swapped.second;

	currentCost = currentSolution.getCost();
	currentSeq  = currentSolution.getSequence();
	newCost     = G.getSwappedCost(si, sj, currentCost, currentSeq);

	if (newCost <= currentCost + T) {
	    // Update the current solution.
	    currentSolution.setCost(newCost);
	    currentSolution.setSequence(newSeq);
	  
	    // Check if the new solution is a minimum.
            minCost = bestSolution.getCost();

	    if (newCost <= minCost) {
		bestSolution.setSequence(newSeq);
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

/**
 * Cools the temperatura while producing a batch 
 * of solutions to the point where the temperature
 * is lower or equal to the given epsilon. This 
 * updates the current solution the heuristic has 
 * produced while also keeping in track the best
 * solution ever produced.
 */
void Heuristic::thresholdAcceptance() {
    double p = 0.0, q = 0.0;

    currentSolution = sweepSolution(currentSolution);
    
    while (temperature > epsilon) {
        q = std::numeric_limits<double>::infinity();
	
	while (p <= q && q >= epsilon) { 
	    q = p;
	    p = calculateBatch(temperature);
	}

	status += getStatus();

	temperature *= coolingFactor;
    }
    
    bestSolution = sweepSolution(bestSolution);
}

/**
 * Sets the best initial temperature for the heuristic
 * to have.
 *
 * @param P A percentage of solutions that have to 
 *     be accepted by temperature.
 */
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

/**
 * Returns the percentage of accepted solutions using
 * the given solution and the temperature.
 * 
 * @param s The solution.
 * @param T The temperature.
 * @return  The percentage of accepted solutions.
 */
double Heuristic::acceptedPercentage(Solution s, double T) {
    double c = 0.0;
    Solution current = s;
    int si, sj;

    double currentCost, newCost;
    std::vector<int> currentSeq, newSeq;

    std::pair<std::pair<int, int>, std::vector<int>> neighborData;
    std::pair<int, int> swapped;
    
    for (int i = 0; i < L; i++) {
        neighborData = currentSolution.getRandomNeighbor();
	swapped      = neighborData.first;
	newSeq       = neighborData.second;

        si = swapped.first;
	sj = swapped.second;

	currentCost = currentSolution.getCost();
	currentSeq  = currentSolution.getSequence();
	newCost     = G.getSwappedCost(si, sj, currentCost, currentSeq);
	
	if (newCost <= currentCost + T) {
	    // Update the current solution
	    current.setCost(newCost);
	    current.setSequence(newSeq);
	    c++;
	}
    }

    return c / L;
}

/**
 * Uses a binary search to find the best temperature 
 * that has the highest percentage of accepted solutions.
 *
 * @param s  The solution.
 * @param T1 The first solution.
 * @param T2 The second solution.
 * @param P  The percentage of accepted solutions.
 * @return   The temperature which fits the most for the heuristic.
 */
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

/**
 * Returns a string representation of the current
 * solution in the heuristic.
 * 
 * @return A string representation of the current
 *     solution in the heuristic.
 */
Solution Heuristic::getCurrentSolution() {
    return currentSolution;
}

/**
 * Returns a string representation of the best
 * solution in the heuristic.
 * 
 * @return A string representation of the best
 *     solution in the heuristic.
 */
std::string Heuristic::printBestSolution() {
    std::string temp;
    temp += "===== BEST SOLUTION =====\n";
    temp += bestSolution.toString() + "\n";
    temp += "Best cost: " + std::to_string(bestSolution.getCost()) + "\n";
    return temp;
}

/**
 * Returns a string representation of the status
 * of the heuristic.
 * 
 * @return A string representation of the status
 *     of the heuristic.
 */
std::string Heuristic::printStatus() {
    std::string temp;
    temp += status;
    temp += "\n ---------- \n";
    temp += printBestSolution();
    return temp;
}

/**
 * Returns a string representation of the cost of 
 * the best solution in the heuristic.
 * 
 * @return A string representation of the cost of
 *     the best solution in the heuristic.
 */
std::string Heuristic::printBestCost() {
   return std::to_string(bestSolution.getCost()) + "\n";
}
