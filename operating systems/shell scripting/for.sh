#!/bin/bash

for var in 1 2 3 4 5
do
	echo $var
done

for var in {10..15}
do 
	echo $var
done

for var in {100..200..10}
do
	echo $var
done


##others

for (( i=0; i<5; i++ ))
do
	echo $i
done


