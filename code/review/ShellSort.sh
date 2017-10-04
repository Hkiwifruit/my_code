#!/bin/bash

function ShellSort(){
    arr=$1
	local gap=$2
	while [ $gap -gt 1 ]
	do
		((gap=gap/3+1))

		for (( i=0; i<$2-gap; i++ ))
		do
			local end=$i
			local temp=${arr[$gap+$end]}

			for (( ;end>=0;end-=gap ))
			do
				if [ ${arr[$end]} -gt $temp ];then
					(( arr[end+gap]=arr[end] ))
				else
					break
				fi
			done
			arr[$end+$gap]=$temp
		done
	done

	return ${arr}
}

arr=(4 5 7 8 9 2 6 0 1 3)
echo ${arr[*]}

ShellSort ${arr} ${#arr[@]}
echo ${arr[*]}
