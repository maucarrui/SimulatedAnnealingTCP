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
 * @param The sequence of cities that represent a path in the Graph.
 * @return The cost of the given solution.
 */
double Graph::getCost(std::vector<int> sequence) {
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

/**
 * Returns the weight of the edge connecting the 
 * city with ID u and ID v.
 * @param u The ID of the city.
 * @param v The ID of the city.
 * @return The weight of the edge.
 */
double Graph::getWeight(int u, int v) {
    int i = searchTable.at(u);
    int j = searchTable.at(v);
    return adjMatrix[i][j];
}

/**
 * Returns the cost of a sequence of cities where two
 * cities will be swapped.
 * @param i    The index of one of the cities that will be swapped.
 * @param j    The index of one of the cities that will be swapped.
 * @param cost The cost of the current sequence.
 * @param s    The sequence of cities.
 * @return     The cost of the sequence of cities swapped.
 */
double Graph::getSwappedCost(int i, int j, double cost, std::vector<int> s) {
    int n = s.size();

    // A total of four edges have been modified
    // in the new path: 
    // e0 = (i-1, i) 
    // e1 = (i, i+1)
    // e2 = (j-1, j)
    // e3 = (j, j+1)
    // So the new cost consist of substracting the 
    // weight of this deleted edges and adding the 
    // new ones.
    double prev_e0 = 0, e0 = 0;
    double prev_e1 = 0, e1 = 0;
    double prev_e2 = 0, e2 = 0;
    double prev_e3 = 0, e3 = 0;
    double diff;

    if (i > 0 && j != i-1) {
        prev_e0 = getWeight(s[i-1], s[i]);
	e0      = getWeight(s[i-1], s[j]);
    }
    
    if (i < n - 1 && j != i+1) {
        prev_e1 = getWeight(s[i], s[i+1]);
	e1      = getWeight(s[j], s[i+1]);
    }

    if (j > 0 && i != j-1) {
        prev_e2 = getWeight(s[j-1], s[j]);
	e2      = getWeight(s[j-1], s[i]);
    }

    if (j < n - 1 && i != j+1) {
        prev_e3 = getWeight(s[j], s[j+1]);
	e3      = getWeight(s[i], s[j+1]);
    }

    diff = (e0 + e1 + e2 + e3) - (prev_e0 + prev_e1 + prev_e2 + prev_e3);

    return cost + (diff / norm);
}

/**
 * Returns the normalization of the graph.
 * @return The normalization of the graph.
 */
double Graph::getNorm() {
    return norm;
}
