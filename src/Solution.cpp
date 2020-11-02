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

    // Index of the cities that will be swapped
    int i = 0, j = 0;
    while (i == j) {
        i = rand() % numCities;
	j = rand() % numCities;
    }
    
    std::vector<int> newSequence = sequence;

    std::string temp1 = "";
    std::string temp2 = "";

    for (int k = 0; k < numCities; k++) {
        temp1 += std::to_string(sequence[k]) + ";";
	temp2 += std::to_string(newSequence[k]) + ";";
    }

    int temp = newSequence[i];
    newSequence[i] = newSequence[j];
    newSequence[j] = temp;

    return Solution(newSequence);
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
