#!/bin/bash

num1=20
num2=5
#addition
echo $((num1+num2)) #for other ops, use - + / %

#another way is to use expr command
echo $(expr $num1 + $num2 )
