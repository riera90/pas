#!/bin/bash
#this script pings a list of ip's and prints a more human readeable version
#ercicio4.sh <imput file> <max waitig (seconds) for response>
file=$1
timeout=$2
ips=$(cat $file | grep -E ^[0-9]) #loads the ips from the file
for ip in $ips; do #iterates all ips
	ping -c 1 -w $2 $ip > /dev/null
	if [[ $? == 0 ]]; then #checks of retval == 0, if so, server is up
		output+=$(ping -c 1 -w $timeout $ip | sed -rn 's/64 bytes from ([0-9.]*): icmp_seq=[0-9]* ttl=[0-9]* time=([0-9,]*).*/La ip \1\t respondio en \2 milisegundos/p') # formats the output
		output+="\n"
	else
		output_failed+="La ip $ip\t no respondió tras $2 segundos\n" #error output
	fi
done
printf "$output" | sort -k 6,6 -n
printf "$output_failed"
