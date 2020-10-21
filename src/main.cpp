#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void parseLine(std::vector<int> &IDs, std::string line) {
    std::stringstream s_stream(line);;
    
    while(s_stream.good()) {
        std::string substring;
	getline(s_stream, substring, ',');
	IDs.push_back( std::stoi(substring) );
    }

}

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
    if (argc < 2) {
        std::cout << "Missing argument: Cities file required.\n";
	return 0;
    } else if (argc > 2) {
        std::cout << "Too many arguments.\n";
	return 0;
    }

    std::string citiesFile = argv[1];
    std::string pathDB     = "sql/database.db";

    std::vector<int> IDs = getIDs(citiesFile);

    return 0;
}
