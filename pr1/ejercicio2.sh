#!/bin/bash
#
# this script shows in human readeable form the files witch size is greater than a value in MB of a given direcroty (no -r)
#
#$1 is the direcroty
#$2 is the minimum size of the file to get sown
find=$(find $1 -maxdepth 1 -mindepth 1 -size +$2M |  tr ";" "\n")
echo "Nombre,LongitudUsuario,FechaModificacion,FechaAcceso,Tamano,Bloques,Permisos,Ejecutable"
for i in $find ;do
	output=$(ls $i -A1 | cut -d "/" -f 2)
	output+=" "
	temp=$(echo $USER | wc -m)
	output+=$(( temp -1 ))
	output+=$( date -r $i "+ %H:%M:%S" )
	output+=$( stat --printf=" %w %X %B %b %A" $i )
	temp=$(stat --printf="%A" $i | grep w | wc -m)
	if [ 0 -lt "$temp" ]
	then
		output+=" 1"
	else
		output+=" 0"
	fi

	echo $output

done
