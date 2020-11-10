# Gensol is a bash script that generates sereval solutions of the TSP problem, trying to find a good solution.

## Number of seeds that will be tried.
maxSeeds=5

## Cities file path.
filepath1=../examples/example1.txt
filepath2=../examples/example2.txt

## Database file path.
database=../sql/database.db

for ((i = 1; i<=$maxSeeds; i++));
do
    echo "40 cities - seed: $i";
    ../build/tsp $filepath1 $database $i;
    echo "150 cities - seed: $i";
    ../build/tsp $filepath2 $database $i;
done
