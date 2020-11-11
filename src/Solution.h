#include <vector>
#include <random>
#include <iostream>
#include <string>

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

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

	std::pair<double, std::vector<int>> getRandomNeighbor(Graph G);

        std::string toString();
};
