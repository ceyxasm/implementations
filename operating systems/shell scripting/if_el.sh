#!/bin/bash

#syntax for if

#if [condition]
#then
# statement
#fi

##interger comparison
# -ne: not equal to- if ["$a" -ne "$b"]
# -rq: is equal to
# -gt: is greater than
# -lt: is less than
# -ge: is greater than or equal to
# -le: is less than or equal to
# <: is than- (("$a" < "$b")) [...]
# <=, >, >=

##String comparisons
# =: is equal- if ["$a" = "$b"]
# ==, !=, <, >, -z (string is not null)
# for <,> use [[]]

count=$1
if [ $count  -eq 9 ]
then 
	echo 9 h
elif [ $count -lt 9 ]
	then echo 9 se less h
else 
	echo 9 se bada h
fi

