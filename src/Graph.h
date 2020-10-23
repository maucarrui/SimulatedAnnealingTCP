#include <map>
#include <vector>

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
        int num_vertex;
        std::map<int, City> vertex;
        std::vector<std::vector<double>> adjMatrix;
	DAO dao;

    public:
	Graph(std::map<int, City> vertex, DAO dao);
	double getMaxDistance();
	// float getNaturalDistance(City a, City b);
};	
