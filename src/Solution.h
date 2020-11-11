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
        double previousCost;
        double cost;
        std::vector<int> previousSequence;
        std::vector<int> sequence;
    
    public:
        Solution();
	Solution(std::vector<int> sequence, double cost);
	
        void setCost(double newCost);
        void setSequence(std::vector<int> newSequence);

	std::vector<int> getSequence();

        double getPreviousCost();
        double getCost();

	void getRandomNeighbor(Graph G);
        void revertChanges();

        std::string toString();
        std::string prevToString();
};
