#!/bin/bash

echo "Input arguments are " "$@"

mpirun -np "$1" --output-filename log "$2"

# concatenate output to a log file
rm -f log
for (( c=0; c<$1; c++ ))
do  
   printf "Rank $c output ----\n" >> log
   cat log.1.$c >> log
   printf "\n" >> log
done

# remove the individual log files
rm log.*

# print concatenated output to terminal
printf "\n"
cat log
