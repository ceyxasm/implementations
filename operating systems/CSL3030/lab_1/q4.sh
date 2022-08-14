#!/bin/bash
#to print 10 random random numbers between 0 and 100 inclusive
read -p 'lower limit: ' l
read -p 'upper limit: ' u
read -p 'total numbers: ' n

awk -v min=$l -v max=$u -v top=$n 'BEGIN {
	srand(69420); 
	counter=0;
	while( counter< top)
		{
		rnd= int( min+rand()*((max-min+1)));
		print rnd;
		counter++;
}
}'

