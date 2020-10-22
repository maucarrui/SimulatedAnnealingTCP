#include <string>

class City {
    private:
        int ID;
	std::string name;
	std::string country;
	int population;
	double latitude;
	double longitude;

    public:
	
	City(int ID, std::string name, std::string country,
	     int population, double latitude, double longitude);

	int getID();
	std::string getName();
	std::string getCountry();
	int getPopulation();
	double getLatitude();
	double getLongitude();
};
