#!/bin/bash

#for com in ls pwd date
#do
#	echo "-------------$com-------------"
#	$com
#done


for item in *
do
	if [ -e $item ]
	then 
		echo $item
	fi
done
