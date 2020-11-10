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
```
Usage: ./tsp <citiesFile.txt> <database.db> <randomSeed> [options] 
Arguments: 
    <citiesFile.txt>   The file contaning the cities' IDs for the TSP.
    <database.db>      The sqlite3 file that contains all the information.
    <randomSeed>       The seed for the RNG.
Options: 
    --verbose          Prints a more detailed execution of the TSP.
```
