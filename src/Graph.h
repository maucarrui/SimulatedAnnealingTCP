#include <map>
#include <list>
#include <vector>
#include <math.h>
#include <iostream>

#ifndef CITY_H
#define CITY_H
#include "City.h"
#endif

#ifndef DAO_H
#define DAO_H
#include "DAO.h"
#endif

class Graph {
    private:
        int numVertex;
        double maxDistance;
        double norm;
        std::map<int, City> vertex;
        std::map<int, int> searchTable;
        std::vector<std::vector<double>> adjMatrix;
	DAO dao;

        double toRadians(double degree);
        void buildSearchTable();
        void buildAdjMatrix();

    public:
	Graph(std::map<int, City> vertex, DAO dao);
	double getMaxDistance();
	double getNaturalDistance(City u, City v);
        double getNormalization();
        double getCost(std::vector<int> sequence);
};	
