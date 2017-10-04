#!/bin/bash

while read line
do
	part1=`echo $line | cut -c 1-3 | tr '[a-z]' '[A-Z]'`
	part2=`echo $line | cut -c 4-6` 
	part3=`echo $line | cut -c 7-9 | tr '[a-z]' '[A-Z]'`
	echo $part3$part2$part1
done < file > file.res
