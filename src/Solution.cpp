#include "Solution.h"

/**
 * Default constructor.
 */
Solution::Solution(){}

/**
 * Solution constructor.
 * A solution for the TSP, a solution is just a sequence of cities.
 */
Solution::Solution(std::vector<int> sequence, double cost) {
    this->sequence = sequence;
    this->cost     = cost;
}

/**
 * Sets the cost for the solution.
 */
void Solution::setCost(double newCost) {
    this->cost = newCost;
}

/**
 * Sets the sequence for the solution.
 */
void Solution::setSequence(std::vector<int> newSequence) {
    this->sequence = newSequence;
}

/**
 * Returns the sequence of the solution.
 */
std::vector<int> Solution::getSequence() {
    return sequence;
}

/**
 * Returns the cost of the solution.
 */
double Solution::getCost() {
    return cost;
}

/**
 * The solution generates a random neighbor, changing 
 * its sequence and its cost. Saving the previous 
 * sequence and the previous cost.
 *
 * @param G The graph to calculate the new cost.
 */
std::pair<double, std::vector<int>> Solution::getRandomNeighbor(Graph G) {
    // Index of the cities that will be swapped
    int numCities = sequence.size();
    int i = 0, j = 0;
    while (i == j) {
        i = rand() % numCities;
	j = rand() % numCities;
    }
    
    // Create the new sequence.
    std::vector<int> newSeq = sequence;
    int temp = newSeq[i];
    newSeq[i] = newSeq[j];
    newSeq[j] = temp;

    // Calculate the new cost.
    double newCost;

    // A total of four edges have been modified
    // in the new path: 
    // e0 = (i-1, i) 
    // e1 = (i, i+1)
    // e2 = (j-1, j)
    // e3 = (j, j+1)
    // So the new cost consist of substracting the 
    // weight of this deleted edges and adding the 
    // new ones.
    double prev_e0 = 0, e0 = 0;
    double prev_e1 = 0, e1 = 0;
    double prev_e2 = 0, e2 = 0;
    double prev_e3 = 0, e3 = 0;
    double diff;

    if (i > 0 && j != i-1) {
        prev_e0 = G.getWeight(sequence[i-1], sequence[i]);
	e0      = G.getWeight(sequence[i-1], sequence[j]);
    }
    
    if (i < numCities - 1 && j != i+1) {
        prev_e1 = G.getWeight(sequence[i], sequence[i+1]);
	e1      = G.getWeight(sequence[j], sequence[i+1]);
    }

    if (j > 0 && i != j-1) {
        prev_e2 = G.getWeight(sequence[j-1], sequence[j]);
	e2      = G.getWeight(sequence[j-1], sequence[i]);
    }

    if (j < numCities - 1 && i != j+1) {
        prev_e3 = G.getWeight(sequence[j], sequence[j+1]);
	e3      = G.getWeight(sequence[i], sequence[j+1]);
    }

    diff = (e0 + e1 + e2 + e3) - (prev_e0 + prev_e1 + prev_e2 + prev_e3);

    newCost = cost + (diff / G.getNorm());

    return std::make_pair(newCost, newSeq);
}

/**
 * Returns a character representation of the solution.
 * @return A character representation of the solution.
 */
std::string Solution::toString() {
    std::string temp;
    int max = sequence.size();

    for (int i = 0; i < max; i++) {
        if (i == max - 1)
	    temp += std::to_string(sequence[i]);
	else
	    temp += std::to_string(sequence[i]) + ",";
    }

    return temp;
}
