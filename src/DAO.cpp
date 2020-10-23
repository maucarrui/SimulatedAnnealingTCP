#include "DAO.h"
#include <iostream>

DAO::DAO(){}

/**
 * Opens a connection to the database.
 *
 * @param nameDB The path of the database file.
 * @return -1 if an error ocurred, 0 otherwise.
 */
int DAO::openDB(const char* pathDB) {
    int exit = sqlite3_open(pathDB, &DB);

    if (exit) {
      std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
      return -1;
    } else {
      // std::cout << "Opened database successfully" << std::endl;
      return 0;
    }
}

/**
 * Returns the city given the ID.
 * 
 * @param ID The ID of the city.
 * @return The city that matches the given ID.
 */
City DAO::getCityByID(int ID) {

    // Cities attributes.
    std::string name;
    std::string country;
    int population;
    double latitude;
    double longitude;

    sqlite3_stmt * stmt;
  
    std::string query = "SELECT * FROM cities WHERE ID = ";
    query = query + std::to_string(ID);

    const char* c_query = query.c_str();

    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);

    name       = std::string( (char *) sqlite3_column_text(stmt, 1) );
    country    = std::string( (char *) sqlite3_column_text(stmt, 2) );
    population = sqlite3_column_int(stmt, 3);
    latitude   = sqlite3_column_double(stmt, 4);
    longitude  = sqlite3_column_double(stmt, 5);

    return City(ID, name, country, population, latitude, longitude);
}
/**
 * Return the distance between two cities.
 *
 * @param a The ID of one city.
 * @param b The other city ID.
 * @return  The distance between the two cities or -1 if there is 
 *          no connection.
 */
double DAO::getConnection(int a, int b) {
  sqlite3_stmt * stmt;

  std::string query = "SELECT * FROM connections WHERE (id_city_1 = ";
  query             = query + std::to_string(a);
  query             = query + " AND id_city_2 = " + std::to_string(b) + ")";
  query             = query + " OR (id_city_1 = " + std::to_string(b);
  query             = query + " AND id_city_2 = " + std::to_string(a) + ")";

  const char* c_query = query.c_str();

  sqlite3_prepare(DB, c_query, -1, &stmt, NULL);
  int res = sqlite3_step(stmt);

  if (res == SQLITE_DONE) {
      return -1;
  } else {
      return sqlite3_column_double(stmt, 2);
  }

}

/**
 * Closes the connection to the database.
 *
 */
void DAO::closeDB() {
    sqlite3_close(DB);
    // std::cout << "Closed database connections successfully." << std::endl;
}
