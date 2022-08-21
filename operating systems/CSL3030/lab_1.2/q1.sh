#!/bin/bash

echo -e "number of processors are : \c"
cat /proc/cpuinfo | grep 'cpu cores' | wc --lines
echo -e "number of cores/processor are :"
cat /proc/cpuinfo | grep 'cpu cores'
echo -e "frequency of each processor at time of execution is  : "
cat /proc/cpuinfo | grep 'MHz'

echo 'description of physical memory at time of execution goes as follows'
free -h
echo -e '\n \n number of forks since boot up are' `vmstat -f`
#cat /proc/cpuinfo | grep 'cpu cores' | wc --lines

