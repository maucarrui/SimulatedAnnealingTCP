#include "Graph.h"

/**
 * Converts degrees to radians.
 */
double Graph::toRadians(double degree) {
    return (M_PI * degree) / 180;
}

/**
 * Graph constructor.
 *
 * @param vertex The vertex of the graph.
 * @param dao    The database access object for the graph.
 */
Graph::Graph(std::map<int, City> vertex, DAO dao) {
    this->numVertex   = vertex.size();
    this->vertex      = vertex;
    this->dao         = dao;
    this->maxDistance = getMaxDistance();

    this->adjMatrix.resize(numVertex, std::vector<double>(numVertex));
    buildAdjMatrix();
}

/**
 * Gets the max distance between any pair of vertex in the graph.
 *
 * @return the max distance.
 */
double Graph::getMaxDistance() {
    int i = 0, j = 1;
    int a, b;
    float max = -1;
    float currentDistance;

    while (i < numVertex - 1) {
        a = vertex.at(i).getID();
	j = i + 1;

	while (j < numVertex) {
             b = vertex.at(j).getID();
	     currentDistance = dao.getConnection(a, b);
	     
	     if (currentDistance > max)
	         max = currentDistance;
	     
	     j++;
        }

	i++;
    }

    return max;
}

/**
 * Calculates the natural distance between two cities.
 *
 * @return The natural distance between two cities.
 */
double Graph::getNaturalDistance(City u, City v) {
    double R = 6373000;

    double latU = toRadians(u.getLatitude());
    double latV = toRadians(v.getLatitude());
    double lonU = toRadians(u.getLongitude());
    double lonV = toRadians(v.getLongitude());

    double temp1 = sin( (lonV - lonU) / 2 );
    double temp2 = sin( (latV - latU) / 2 );

    double term1 = pow(temp2, 2);
    double term2 = cos(latU) * cos(latV) * pow(temp1, 2);

    double A = term1 + term2;

    double root1 = sqrt(A);
    double root2 = sqrt(1 - A);

    double C = 2 * atan2(root1, root2);

    return R * C;
}

/**
 * Builds the adjacency matrix of the graph.
 */
void Graph::buildAdjMatrix() {
    double distance;

    for (int i = 0; i < numVertex; i++) {
	City u = vertex.at(i);

        for (int j = 0; j < numVertex; j++) {
	    City v = vertex.at(j);
	    
	    distance = dao.getConnection(u.getID(), v.getID());
	    
	    if (distance > -1)
	        adjMatrix[i][j] = distance;
	    else
	        adjMatrix[i][j] = maxDistance * getNaturalDistance(u, v);
	}
    }
}
