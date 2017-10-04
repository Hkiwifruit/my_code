#!/bin/bash

i=0
str=''
arr=('|' '/' '-' '\\')
while(( i <= 100))
do
	#printf "\033[42m\033[1m"
	printf "[\033[42m%-100s\033[1m][%d%%][%c\033[1m]\r" "$str" "$i" "${arr[index]}"
	let i++
	let index=i%4
	str=$str" "
	sleep 0.05
done
echo
