#!/bin/sh
if [ -n "$1" ]
then
	echo "$1"
	find $1 -name "*.c" -exec ./replace.sh {} \;
	find $1 -name "*.h" -exec ./replace.sh {} \;
else
	echo "Usage: ./recomment.sh <dir>"
fi


