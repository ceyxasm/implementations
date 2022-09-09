#!/bin/bash

#a shell script to translate the current date and time in word format.
echo "current time: " `date +%r`

h=`date +%-H`
m=`date +%-M`
s=`date +%-S`

post='AM'

ones=(zero one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen ninteen)

tens=(zero ten twenty thirty fourty fifty sixty)

if [ $h -gt 12 ]
then 
	let "h -=12"
	post='PM'
fi

if [ $h -eq 0 ]
then let "h = 12"
fi

function getnos(){
	if [ $1 -lt 20 ]
	then tword=${ones[$1]}
	else 
		first=`expr $1 / 10`
		second=`expr $1 % 10`
		if [ $second -eq 0 ]
		then tword=${tens[$first]}
		else
			tword="${tens[$first]}-${ones[$second]}"
		fi
	fi
}

tword="global"

getnos $h
word_h=$tword

getnos $m
word_m=$tword

getnos $s
word_s=$tword

echo "time is: $word_h hours, $word_m minutes and $word_s seconds $post"



