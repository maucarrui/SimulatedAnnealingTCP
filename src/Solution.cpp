#include "Solution.h"

/**
 * Default constructor.
 */
Solution::Solution(){}

/**
 * Solution constructor.
 * A solution for the TSP, a solution is just a sequence of cities.
 */
Solution::Solution(std::vector<int> sequence) {
    this->sequence = sequence;
}

/**
 * Returns the sequence of the solution.
 */
std::vector<int> Solution::getSequence() {
    return sequence;
}

/**
 * Returns a random neighbor of the current solution.
 * This random neighbor is obtained swapping two random 
 * cities in the sequence.
 */
Solution Solution::getRandomNeighbor() {
    int numCities = sequence.size();
    std::uniform_int_distribution<int> distribution(0, numCities - 1);

    // Index of the cities that will be swapped
    int i = 0, j = 0;
    while (i == j) {
        i = rand() % numCities;
	j = rand() & numCities;
    }
    
    std::vector<int> newSequence = sequence;
    int temp = newSequence[i];
    newSequence[i] = newSequence[j];
    newSequence[j] = temp;

    return Solution(newSequence);
}
