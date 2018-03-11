#!/bin/bash
index=0
output=""
for it in $(cat $1 | grep -E ^[0-9]); do output+=$(ping -c 1 $it | sed -rn 's/64 bytes from ([0-9.:]*) icmp_seq=[0-9]* ttl=[0-9]* time=([0-9,]*).*/La ip \1 respondio en \2 milisegundos/p') ; output+="\n" ; done
# for it in $(cat $1 | grep -E ^[0-9]); do echo $(ping -c 1 $it | grep -Eo '64 bytes from ([0-9.:]*) icmp_seq=[0-9]* ttl=[0-9]* time=([0-9,]*).*') ; done
printf "$output" | sort 
