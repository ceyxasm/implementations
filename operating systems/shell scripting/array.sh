#!/bin/bash

os=('ubuntu' 'kali' 'pop')
echo "${os[@]}" #for printing all the elements

echo "${!os[@]}" #rather prints the inde

echo "${#os[@]}" # rather prints the length

#to add an element in array

os[5]='mac' ## if index specified doesnt exist then, its appended 
	    ## else it modifies the array
echo "${!os[@]}"

## to delete we use the term unset and index

unset os[8] #if index doesnt exit, nothing happens
echo "${os[@]}"


