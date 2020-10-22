#include <sqlite3.h>
#include <string>

#include "City.h"

class DAO {
    private:
    
        sqlite3* DB;

    public:
        
        DAO();
        int openDB(const char* pathDB);
        City getCityByID(int ID);
        void closeDB();
};
