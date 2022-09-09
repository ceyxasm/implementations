#!/bin/bash

read -p 'enter process name: ' process
pid=`pgrep $process`
echo "pid of $process is $pid"
ppid=`ps -o ppid= -p $pid`
counter=1
while ! [[ $ppid -eq 1 || $counter -ge 5 ]]
do
	echo "parent$counter pid: $ppid"
	ppid=`ps -o ppid= -p $ppid`
	let "counter=counter+1"
done	

echo "parent$counter pid: $ppid"
