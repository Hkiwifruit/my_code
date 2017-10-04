#!/bin/bash

proc=$0
usage(){
	printf "%s %s" "proc" "nums"
}

fib(){
	if [ $1 -lt  ];then
		usage
	fi
	local datap=$(( nums-1 ))


}

#fib(){
#	num=$1
#	f=1
#	s=1
#	t=1
#	i=3
#	while [ $i -le $num ]
#	do
#		let t=$f+$s
#		let f=s
#		let s=t
#		let i++
#	done
#	echo $s
#}
#fib
#arr[]=("$a" "$b" "$c")
#${arr[1]}=1
#${arr[2]}=1
#sum=0
#
#while(( i < n ))
#do
#	$sum=(( ${arr[1]} + ${arr[2]} ))
#	${arr[3]}=sum
#	${}
#done
