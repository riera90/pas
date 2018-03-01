#!/bin/bash
varh=$(ls *.c | wc -l)
varc=$(ls *.h | wc -l)
var=$((varc+varh))
all=$(ls *.c )
all+=" "
all+=$(ls *.h )
if [ $var -lt 1 ];
then
	echo "no hay archivos .c o .h en este directorio"
else
	top=-1
	echo -e "hay $var ficheros .c o .h"
	for (( i = 0; i < $var; i++ )); do
		max_size=$((0))
		max_file="ndef"


		for it in $all ; do
			size=$(cat $it | wc -m)
			# echo -e "size to check: $size | max: $max_size | top: $top"
			if [ $((max_size)) -lt $((size)) ] ; then
				# echo "checking!"
				if [[ $top -eq $((-1)) ]] ; then
					# echo ">>>>>>>>>>>>>>>new<<<<<<<<<<<<<<<"
					max_file=$it
					max_size=$size
					# echo -e "new file: $max_file"
					# echo -e "new size: $max_size"
				else
					if [[ $top -gt $size ]] ; then
						# echo ">>>>>>>>>>>>>>>new not def<<<<<<<<<<<<<<<"
						max_file=$it
						max_size=$size
						# echo -e "new file: $max_file"
						# echo -e "new size: $max_size"
					fi
				fi

			fi


		done
		top=$((max_size-1))
		echo -e "fichero: $max_file \t lineas: $(cat $max_file | wc --lines) \t caracteres: $max_size"
	done
fi
