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
 * Generates a random neighbor of the current solution,
 * this is done by swapping two cities in the sequence
 * of the solution. The method returns the indexes of 
 * the swapped cities and the new sequence.
 * @return A pair containing the pair of indexes that 
 *   were swapped and the new sequence.
 */
std::pair<std::pair<int, int>, std::vector<int>> Solution::getRandomNeighbor() {
    // Index of the cities that will be swapped
    int numCities = sequence.size();
    int i = 0, j = 0;
    while (i == j) {
        i = rand() % numCities;
	j = rand() % numCities;
    }

    std::pair<int, int> swapped = std::make_pair(i, j);
    
    // Create the new sequence.
    std::vector<int> newSeq = sequence;
    int temp = newSeq[i];
    newSeq[i] = newSeq[j];
    newSeq[j] = temp;

    return std::make_pair(swapped, newSeq);
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
