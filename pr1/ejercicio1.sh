#!/bin/bash
#this scipt counts and order all c source code files by number of characters
varh=$(ls *.c | wc -l)
varc=$(ls *.h | wc -l)
var=$((varc+varh))
all=$(ls *.c )
all+=" "
all+=$(ls *.h )
if [ $var -lt 1 ] ; then
	echo "no hay archivos .c o .h en este directorio"
else
	top=-1
	echo -e "hay $var ficheros .c o .h"
	for (( i = 0; i < $var; i++ )); do
		max_size=$((0))
		max_file="ndef"
		for it in $all ; do
			size=$(cat $it | wc -m)
			if [ $((max_size)) -lt $((size)) ] ; then
				if [[ $top -eq $((-1)) ]] ; then
					max_file=$it
					max_size=$size
				else
					if [[ $top -gt $size ]] ; then
						max_file=$it
						max_size=$size
					fi
				fi
			fi
		done
		top=$((max_size-1))
		echo -e "fichero: $max_file \t lineas: $(cat $max_file | wc --lines) \t caracteres: $max_size"
	done
fi
