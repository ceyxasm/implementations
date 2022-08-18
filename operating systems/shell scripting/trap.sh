#!/bin/bash

trap "echo Exit command by C^" 0 2 15

echo "pid is $$"
while (( COUNT < 10 ))
do
	sleep 10
	(( COUNT ++ ))
	echo $COUNT
done
exit 0
