#!/bin/bash
#a shell script to find out the three largest directories/files for a given directory.

dir=$1
read -p 'number of dir/files to be returned: ' no

#if  [ -e $dir ]
#then 
#	echo not a directory
#	exit 0
#if ! [ -s $dir ]
#then 
#	echo directory is empty
#	exit 0
#fi

#echo -e "number of largest dirs to be returned: \c"
#read no

if [ -f $dir ]
then dir='*'
else dir=$dir'/*'
fi
du -sm $dir | sort -nr | head -n $no
