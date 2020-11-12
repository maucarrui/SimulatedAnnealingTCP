#include <vector>
#include <random>
#include <iostream>
#include <string>

class Solution {
    private:
        double cost;
        std::vector<int> sequence;
    
    public:
        Solution();
	Solution(std::vector<int> sequence, double cost);
	
        void setCost(double newCost);
        void setSequence(std::vector<int> newSequence);

        double getCost();
	std::vector<int> getSequence();

	std::pair<std::pair<int, int>, std::vector<int>> getRandomNeighbor();

        std::string toString();
};
