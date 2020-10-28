#include <vector>
#include <random>
#include <iostream>

class Solution {
    private:
        std::vector<int> sequence;
    
    public:
        Solution();
	Solution(std::vector<int> sequence);
	
	std::vector<int> getSequence();
	Solution getRandomNeighbor();
};
