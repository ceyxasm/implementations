#!/bin/bash

# a shell script to find out the number of lines and words in a given file.

echo -e "enter file name (file should be in same dir as the script): \c"
read file_name

if ! [ -e $file_name ]
then echo "$file_name doesnt exist"
#elif ! [ -c $file_name ]
#then echo "$file_name is an invalid file"
elif ! [ -s $file_name ]
then echo "$file_name is empty file"
else 
	lines=`wc --lines < $file_name`
	words=`wc --words < $file_name`
	chars=`wc -m < $file_name`
	echo "no. of lines: $lines"
	echo "no. of words: $words"
	echo "no. of chars: $chars"
fi


