#!/bin/bash

start=$(date +%s.%N)
./astar/solver $1 > /dev/null
end=$(date +%s.%N)    
runtime1=$(python -c "print(${end} - ${start})")
echo "Astar take $runtime1 s"

start=$(date +%s.%N)
./breadth/solver $1 > /dev/null
end=$(date +%s.%N)    
runtime2=$(python -c "print(${end} - ${start})")
echo "Breadth take $runtime2 s"

start=$(date +%s.%N)
./depth/solver $1 > /dev/null
end=$(date +%s.%N)    
runtime3=$(python -c "print(${end} - ${start})")
echo "Depth take $runtime3 s"
