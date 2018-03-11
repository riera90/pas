#!/bin/bash
#this script pings a list of ip's and prints a more human readeable version
#eercicio4.sh <imput file> <max waitig (seconds)>
for it in $(cat $1 | grep -E ^[0-9]); do #iterates all ips of the file
	temp=$(ping -c 1 -w $2 $it)
	if [[ $? == 0 ]]; then #checks of retval == 0 if so, server is up
		output+=$(ping -c 1 -w $2 $it | sed -rn 's/64 bytes from ([0-9.]*): icmp_seq=[0-9]* ttl=[0-9]* time=([0-9,]*).*/La ip \1 respondio en \2 milisegundos/p') # formats the output
		output+="\n"
	else
		output_failed+="La ip $it no respondió tras $2 segundos\n" #error output
	fi
done
printf "$output" | sort -k 6,6 -n
printf "$output_failed"
