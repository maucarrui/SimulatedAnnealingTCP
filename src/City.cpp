#include "City.h"

City::City(int ID, std::string name, std::string country,
	   int population, double latitude, double longitude) {
    this->ID         = ID;
    this->name       = name;
    this->country    = country;
    this->population = population;
    this->latitude   = latitude;
    this->longitude  = longitude;
}

int City::getID() {
    return this->ID;
}

std::string City::getName() {
    return this->name;
}

std::string City::getCountry() {
    return this->country;
}

int City::getPopulation() {
    return this->population;
}

double City::getLatitude() {
    return this->latitude;
}

double City::getLongitude() {
    return this->longitude;
}
