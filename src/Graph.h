#include <map>
#include <list>
#include <vector>
#include <math.h>

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
        std::vector<std::vector<double>> adjMatrix;
	DAO dao;

        double toRadians(double degree);
        void buildAdjMatrix();

    public:
	Graph(std::map<int, City> vertex, DAO dao);
	double getMaxDistance();
	double getNaturalDistance(City u, City v);
        double getNormalization();
};	
