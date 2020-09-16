#!/bin/bash

start=$(date +%s.%N)
./opti/solver $@
ret=`echo $?`
test=1
if [ $ret -eq $test ]
then
    ./depth $@
else
    ./astar $@
fi
end=$(date +%s.%N)
runtime1=$(python -c "print(${end} - ${start})")
echo "Solved in $runtime1"
