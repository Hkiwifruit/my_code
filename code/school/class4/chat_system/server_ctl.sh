#!/bin/bash

ROOT_PATH=$(pwd)
conf=$ROOT_PATH/conf/server.conf
server=$ROOT_PATH/udpServer

_proc=$(basename $0)
function usage(){
	printf "Usage: %s [-s(start)|-t(stop)|-rs(restart)]\n" "$_proc"
}

function Start(){
	name=$(basename $server)
	if `pidof $name>>/dev/null`;then
		echo "server is already running!"
	else
		port=$(awk -F: '/^PORT/{print $NF}' $conf)
		ip=$(awk -F: '/^IP/{print $NF}' $conf)
		$server $ip $port
	fi
}

function Stop(){
	name=$(basename $server)
	pid=$(pidof $name)
	if $?;then
		kill -9 $pid
	else
		echo "server is not running!"
	fi
}

function Restart(){
	Stop
	Start
}

if [ $# -ne 1 ];then
	usage;
	exit 1;
fi

case $1 in
	-s | start )
		Start
	;;
	-t | stop )
		Stop
	;;
	-rt | restart )
		Restart
	;;
	* )
		usage
		exit 1;
	;;
esac
