#!/bin/bash
varh=$(ls -l | grep .h | wc -l)
varc=$(ls -l | grep .c | wc -l)
var=$((varc+varh-4))
if [ $var -lt 1 ];
then
	echo "no hay archivos .c o .h en este directorio"
else
	echo -e "hay $var ficheros .c o .h"
fi
