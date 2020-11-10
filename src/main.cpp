#include <iostream>
#include <cstdlib>
#include <ctime>
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

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.h"
#endif

#ifndef HEURISTIC_H
#define HEURISTIC_H
#include "Heuristic.h"
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

/**
 * Returns the usage of this program.
 * @return the usage of this program.
 */
std::string usage() {
    std::string s = "";
    s += "Usage: ./tsp <citiesFile.txt> <database.db> <randomSeed> [options] \n";
    s += "Arguments: \n";
    s += "    <citiesFile.txt>   The file contaning the cities' IDs for the TSP.\n";
    s += "    <database.db>      The sqlite3 file that contains all the information.\n";
    s += "    <randomSeed>       The seed for the RNG.\n";
    s += "Options: \n";
    s += "    --verbose          Prints a more detailed execution of the TSP.\n";

    return s;
}

int main(int argc, char** argv) {

    bool activeOption = false;

    // Handle too few or too many arguments.
    if (argc < 2 || argc > 5) {
        std::cout << usage() << std::endl;
	return -1;
    } else if (argc == 5) {
        std::string option = "--verbose";
        if (!option.compare(argv[4]))
	    activeOption = true;
	else {
	    std::cout << usage() << std::endl;
	    return -1;
	}
    }
    
    // Get the input file, the sql file and the seed.
    std::string citiesFile = argv[1];
    const char* pathDB     = argv[2];
    int seed               = std::stoi(argv[3]);

    // Set a random seed for the random number generation.
    std::srand(seed);

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

    // Definition of the heuristic.

    Graph g                   = Graph(cities, dao);
    Solution initialSolution  = Solution(IDs);
    double initialTemperature = 139000;
    double coolingFactor      = 0.9;
    double epsilon            = 0.0010;
    double epsilon_p          = 0.0010;
    double L                  = 3000;

    Heuristic h = Heuristic(g, 
			    initialSolution,
			    initialTemperature,
			    coolingFactor,
			    L,
			    epsilon,
			    epsilon_p);

    h.getInitialTemperature(0.90);

    h.thresholdAcceptance();

    if (activeOption)
        std::cout << h.printStatus();
    else
        std::cout << h.printSolution();

    dao.closeDB();

    return 0;
}
