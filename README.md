# Simulated Annealing TCP
Solution generation of the Travelling Salesman Problem using the simulated annealing heuristic.


## Requirements 
* G++ (GCC) >= 10.2.0
* Sqlite3 >= 3.33.0
* Meson >= 0.55.3

## How to compile

Build directory
```
meson builddir
```

Compile
```
cd builddir
ninja
```

## Usage
You'll need two files, the file which contains the cities' IDs and the sqlite3 database file (.db).

```
./tsp path/to/citiesIDs.txt path/to/database.db
```
