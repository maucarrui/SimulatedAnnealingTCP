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
    --onlycost         Prints only the cost of the best found solution.
```

## Best found solutions.
For the first example containing a total of 40 cities, the best solution 
that was found had the following cost:
``` 
===== BEST SOLUTION =====
7,823,816,982,332,820,654,490,653,656,2,661,657,168,1,815,496,172,163,329,493,979,4,165,3,333,981,6,5,978,817,489,492,491,984,164,331,871,327,980
Best cost: 0.220064
```

For the second example, containing a total of 150 cities, the best solution
that was found had the following cost:
```
===== BEST SOLUTION =====
494,495,167,328,326,1037,169,1073,330,819,655,818,666,658,166,822,74,1001,297,980,336,840,350,20,660,510,343,349,984,499,347,817,4,174,5,6,988,165,3,353,332,181,14,982,187,345,654,820,26,185,22,351,981,990,27,333,991,676,665,344,653,490,1004,978,352,668,176,23,489,25,492,491,334,674,871,985,500,825,670,327,511,504,999,8,662,331,1003,11,164,501,17,186,671,179,652,1075,483,171,346,183,75,821,512,16,520,675,340,502,1038,12,828,151,339,826,444,995,837,979,493,509,329,168,505,815,816,678,823,7,507,661,829,1,9,986,508,657,663,832,184,667,656,2,173,839,19,496,172,182,673,163
Best cost: 0.177675
```
