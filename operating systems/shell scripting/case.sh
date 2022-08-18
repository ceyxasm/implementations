#!/bin/bash

##SYNTAX
# case expression in
#	pattern1 )
#		statements ;;
#	pattern2 )
	#	statements ;;
# esac

animal=$1

case $animal in
	"cat" )
		echo "this mf meows" ;;
	"dog" )
		echo "this mf barks" ;;
	"cow" )
		echo "this mf moos" ;;
	* ) #default
		echo "kuch bhi" ;;
esac
