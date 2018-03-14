#!/bin/bash
#this script prints a human readeable version of various files of /proc
#ejercicio6.sh
lines=$(cat /etc/group | sed -rn 's/^([a-z\-]*):.:([0-9]*):.*/\2,\1/p')
#generates a GUI dictionary called group
for line in $lines ; do
	index=$(echo $line | grep -Eo '[0-9]*')
	word=$(echo $line | grep -Eo '[a-z\-]*')
	group["$index"]="$word"
done
passwd=$(cat /etc/passwd | sed -rn 's/^([a-z\-]*):x:([0-9]*):([0-9]*):([a-zA-Z\-\/]*):([\/a-z]*):([\/a-z]*)/logname:·\1;_->IUD:·\2;_->GUID:·\3;_->group:·xxx;_->gecos:·\4;_->home:·\5;_->shell:·\6/p' | grep $1)
for user in $passwd ; do
	GUID=$(echo "$user" | sed -rn 's/.*GUID:·([0-9]*).*/\1/p')
	for user_ in $(users) ; do
		if [[ "$(echo "$user" | sed -rn 's/logname:·([a-zA-Z\-]*).*/\1/p')" == "$user_" ]]; then
			conected=1
			break
		else
			conected=0
		fi
	done
	printf "${group[$GUID]}-$user" | sed -rn 's/(^[a-z]*)-(.*)xxx(.*$)/\2\1\3/p' | tr ';' '\n' | tr '_' '\t' | tr '·' ' '
	printf "\n\t->loged: $conected\n"
done
