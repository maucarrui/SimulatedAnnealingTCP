#include <sqlite3.h>
#include <string>

#ifndef CITY_H
#define CITY_H
#include "City.h"
#endif

class DAO {
    private:
    
        sqlite3* DB;

    public:
        
        DAO();
        int openDB(const char* pathDB);
        City getCityByID(int ID);
        double getConnection(int a, int b);
        void closeDB();
};
