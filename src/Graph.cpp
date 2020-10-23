#include "Graph.h"

/**
 * Graph constructor.
 *
 * @param vertex The vertex of the graph.
 * @param dao    The database access object for the graph.
 */
Graph::Graph(std::map<int, City> vertex, DAO dao) {
    int no_columns   = vertex.size();
    this->num_vertex = vertex.size();
    this->vertex     = vertex;
    this->dao        = dao;
    this->adjMatrix.resize(no_columns, std::vector<double>(no_columns));
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

    while (i < num_vertex - 1) {
        a = vertex.at(i).getID();
	j = i + 1;

	while (j < num_vertex) {
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
