#!/bin/bash

#echo enter name
read -p 'name: ' name
echo the name entered was $name
echo
echo "enter DOB (DD/MM/YY)"
read date month year
echo date $date
echo month $month
echo year $year
echo
#but sometimes we need to take input on the same line, and for that
read -p 'enter your dpt rank ' rank
read -sp 'enter your CGPA ' cg

echo
echo  $rank $cg

echo enter numbers
read -a nums
echo ${nums[0]} ${nums[1]} ${nums[2]}  
