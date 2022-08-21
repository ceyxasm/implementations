#!/bin/bash

file_name=$1

output_file=$2

if ! [ -e $file_name ]
then echo file does not exist
	exit 1
elif ! [ -s $file_name ]
then echo file is empty
	exit 1
else
	lines=`wc --lines < $file_name`
	words=`wc --words < $file_name`
	bytes=`wc -m < $file_name`
	echo "lines : $lines">>$2
	echo "words : $words">>$2
	echo "bytes : $bytes">>$2

	echo "contents of $2 are"
	cat $2
fi	


