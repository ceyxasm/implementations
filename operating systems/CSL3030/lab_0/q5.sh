#!/bin/bash
#a command using sed to print first 5 lines of a file.

path_2_file=$1

if ! [ -f $path_2_file ]
then echo "invalid file format"
elif ! [ -s $path_2_file ]
then echo "file is empty"
else sed -n '1,5p' $path_2_file
fi	
