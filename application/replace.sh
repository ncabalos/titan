#!/bin/sh
echo "$1"
sed 's,//\(.*\),/*\1 */,' $1 > $1.tmp
sed "s/\x0d\x20/\x20/" $1.tmp > $1
sed "s:\/\*\x20:\/\*:" $1 > $1.tmp
sed "s:\/\*:\/\*\x20:" $1.tmp > $1
sed "s:\/\*\x20\*:\/\*\*:" $1 > $1.tmp
cp $1.tmp $1
rm $1.tmp
