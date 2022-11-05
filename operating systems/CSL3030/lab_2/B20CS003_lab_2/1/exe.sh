#!/bin/bash
g++ flip.cpp -o flip
g++ counter.cpp -o counter
g++ driver.cpp -o driver
clear
./driver input.txt output.txt

echo 
echo flushing contents of output.txt 
cat output.txt


