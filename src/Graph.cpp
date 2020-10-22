#include "Graph.h"

/**
 * Graph constructor.
 *
 * @param vertex The vertex of the graph.
 * @param dao    The database access object for the graph.
 */
Graph::Graph(std::map<int, City> vertex, DAO dao) {
    int no_columns = vertex.size();
    this->vertex    = vertex;
    this->dao       = dao;
    this->adjMatrix.resize(no_columns, std::vector<double>(no_columns));
}
