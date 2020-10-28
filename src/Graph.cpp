#include "Graph.h"

/**
 * Converts degrees to radians.
 */
double Graph::toRadians(double degree) {
    return (M_PI * degree) / 180;
}

/**
 * Default constructor.
 */
Graph::Graph(){}

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
    this->norm        = getNormalization();

    this->adjMatrix.resize(numVertex, std::vector<double>(numVertex));
    buildSearchTable();
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
    double max = -1;
    double currentDistance;

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
 * Gets the normalization of the graph.
 *
 * @return The normalization of the graph.
 */
double Graph::getNormalization() {
    std::list<double> distances;

    // Gets all the posible distances in the graph.
    int i = 0, j = 1;
    int a, b;
    double currentDistance;

    while (i < numVertex - 1) {
        a = vertex.at(i).getID();
	j = i + 1;

	while (j < numVertex) {
             b = vertex.at(j).getID();
	     currentDistance = dao.getConnection(a, b);

	     if (currentDistance > -1)
	         distances.push_back(currentDistance);

	     j++;
        }

	i++;
    }

    // Gets the sum of the first |V|-1 distances
    distances.sort(std::greater<double>());
    std::list<double>::iterator it;
    double normalization = 0;

    i = 0;
    for (it = distances.begin(); it != distances.end(); it++) {
        if (i >= numVertex-1)
	    break;

	normalization += *it;
	i++;
    }

    return normalization;
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

    double temp1 = sin((lonV - lonU) / 2);
    double temp2 = sin((latV - latU) / 2);

    double term1 = pow(temp2, 2);
    double term2 = cos(latU) * cos(latV) * pow(temp1, 2);

    double A = term1 + term2;

    double root1 = sqrt(A);
    double root2 = sqrt(1 - A);

    double C = 2 * atan2(root1, root2);

    return R * C;
}

/**
 * Builds the search table of a Graph. Given the ID of the city,
 * the search table returns the index corresponding to that 
 * city in the adjacency matrix.
 */
void Graph::buildSearchTable() {
    int ID, index;
    std::map<int, City>::iterator it;

    for (it = vertex.begin(); it != vertex.end(); it++) {
        ID    = it->second.getID();
	index = it->first;

        searchTable.emplace(ID, index);
    }
}

/**
 * Builds the adjacency matrix of the graph.
 */
void Graph::buildAdjMatrix() {
    double natural;
    double distance;

    for (int i = 0; i < numVertex; i++) {
	City u = vertex.at(i);

        for (int j = 0; j < numVertex; j++) {
	    City v = vertex.at(j);
	    
	    distance = dao.getConnection(u.getID(), v.getID());
	    
	    if (distance > -1) {
	        adjMatrix[i][j] = distance;
		adjMatrix[j][i] = distance;
	    }
	    else {
	        natural = getNaturalDistance(u, v);
	        adjMatrix[i][j] = maxDistance * natural;
		adjMatrix[j][i] = maxDistance * natural;
	    }
	}
    }
}

/**
 * Calculates the cost of the given solution.
 * 
 * @param The solution which contains a sequence of cities 
 *     that represent a path in the Graph.
 * @return The cost of the given solution.
 */
double Graph::getCost(Solution s) {
    std::vector<int> sequence = s.getSequence();

    double travelledDistance = 0;
    int indexU, indexV;

    std::vector<int>::iterator it = sequence.begin();
    std::vector<int>::iterator jt = sequence.begin();
    
    jt++;

    while (jt != sequence.end()) {
        indexU = searchTable.at(*it);
	indexV = searchTable.at(*jt);
        travelledDistance += adjMatrix[indexU][indexV];
	it++;
	jt++;
    }

    return travelledDistance / norm;
}
