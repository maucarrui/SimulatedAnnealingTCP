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
 * Returns the previous cost of the solution.
 */
double Solution::getPreviousCost() {
    return previousCost;
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
void Solution::getRandomNeighbor(Graph G) {
    // Save the previous sequence and cost.
    previousSequence = sequence;
    previousCost     = cost;

    // Index of the cities that will be swapped
    int numCities = sequence.size();
    int i = 0, j = 0;
    while (i == j) {
        i = rand() % numCities;
	j = rand() % numCities;
    }
    
    // Create the new sequence.
    int temp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;

    // Calculate the new cost.

    // A total of four edges have been modified
    // in the new path: 
    // e0 = (i-1, i) 
    // e1 = (i, i+1)
    // e2 = (j-1, j)
    // e3 = (j, j+1)
    // So the new cost consist of substracting the 
    // weight of this deleted edges and adding the 
    // new ones.
    long double prev_e0 = 0, e0 = 0;
    long double prev_e1 = 0, e1 = 0;
    long double prev_e2 = 0, e2 = 0;
    long double prev_e3 = 0, e3 = 0;

    if (i > 0 && j != i-1) {
        prev_e0 = G.getWeight(previousSequence[i-1], previousSequence[i]);
	e0      = G.getWeight(sequence[i-1], sequence[i]);
    }
    
    if (i < numCities - 1 && j != i+1) {
        prev_e1 = G.getWeight(previousSequence[i], previousSequence[i+1]);
	e1      = G.getWeight(sequence[i], sequence[i+1]);
    }

    if (j > 0 && i != j-1) {
        prev_e2 = G.getWeight(previousSequence[j-1], previousSequence[j]);
	e2      = G.getWeight(sequence[j-1], sequence[j]);
    }

    if (j < numCities - 1 && i != j+1) {
        prev_e3 = G.getWeight(previousSequence[j], previousSequence[j+1]);
	e3      = G.getWeight(sequence[j], sequence[j+1]);
    }

    cost *= G.getNorm();
    cost += (e0 + e1 + e2 + e3) - (prev_e0 + prev_e1 + prev_e2 + prev_e3);
    cost /= G.getNorm();
}

/**
 * Returns to the previous statue of the solution.
 */
void Solution::revertChanges() {
    sequence = previousSequence;
    cost     = previousCost;
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

/**
 * Returns a character representation of the previous solution.
 * @return A character representation of the previous solution.
 */
std::string Solution::prevToString() {
    std::string temp;
    int max = sequence.size();

    for (int i = 0; i < max; i++) {
        if (i == max - 1)
	    temp += std::to_string(previousSequence[i]);
	else
	    temp += std::to_string(previousSequence[i]) + ",";
    }

    return temp;
}
