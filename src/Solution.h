#include <vector>
#include <random>
#include <iostream>
#include <string>

class Solution {
    private:
        double previousCost;
        double cost;
        std::vector<int> previousSequence;
        std::vector<int> sequence;
    
    public:
        Solution();
	Solution(std::vector<int> sequence, double cost);
	
        void setCost();
        void setSequence();

	std::vector<int> getSequence();

        double getPreviousCost();
        double getCost();

	void getRandomNeighbor();

        std::string toString();
};
