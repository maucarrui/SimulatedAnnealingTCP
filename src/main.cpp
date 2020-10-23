#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#ifndef DAO_H
#define DAO_H
#include "DAO.h"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

/**
 * Parses the current line, separating each substring
 * delimited by a comma and casting it into an int, 
 * finally pushing it into the vector.
 *
 * @param IDs  The current IDs that have been read.
 * @param line The line containing the IDs.
 */
void parseLine(std::vector<int> &IDs, std::string line) {
    std::stringstream s_stream(line);;
    
    while(s_stream.good()) {
        std::string substring;
	getline(s_stream, substring, ',');
	IDs.push_back( std::stoi(substring) );
    }

}

/**
 * Gets the IDs of the cities given in the file passed by
 * argument.
 *
 * @param  fileName The name of the file containing the IDs.
 * @return A vector containing all of the IDs in the file.
 */
std::vector<int> getIDs(std::string fileName) {
     std::vector<int> IDs;
     std::string line;
     
     std::ifstream fileIDs(fileName);

     if (fileIDs.is_open()) {
         while (getline(fileIDs, line)) {
             parseLine(IDs, line);
	 }
     }
     
     fileIDs.close();
     return IDs;
}

int main(int argc, char** argv) {

    // Handle too few or too many arguments.
    if (argc < 2) {
        std::cout << "Missing argument: Cities file required.\n";
	return 0;
    } else if (argc > 2) {
        std::cout << "Too many arguments.\n";
	return 0;
    }

    std::string citiesFile = argv[1];
    const char* pathDB     = "sql/database.db";

    // Get the IDs from the file.
    std::vector<int> IDs = getIDs(citiesFile);

    // Get the cities.
    DAO dao;
    std::map<int, City> cities;

    dao.openDB(pathDB);

    int i = 0;
    for(int j : IDs) {
        cities.emplace(i, dao.getCityByID(j));
	i++;
    }

    Graph g = Graph(cities, dao);

    City tokyo   = dao.getCityByID(1);
    City shangai = dao.getCityByID(2);

    double norm = g.getNormalization();

    std::cout.precision(10);
    std::cout << g.getNaturalDistance(tokyo, shangai) << std::endl;
    std::cout << norm << std::endl;


    double cost = g.getCost(IDs);

    std::cout << cost << std::endl;

    dao.closeDB();

    return 0;
}
