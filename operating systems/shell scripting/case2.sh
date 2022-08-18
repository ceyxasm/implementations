#!/bin/bash

read -p 'enter char ' value

case $value in
	[a-z] )
		echo 'is lowercase' ;;
	[A-Z] )
		echo 'is uppercase' ;;
	[0-9] )
		echo 'is digit' ;;
	? )
		echo 'is special char' ;;
	* )
		echo 'char ni h' ;;
esac
