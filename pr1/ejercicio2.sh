#!/bin/bash<ul>
#
# this script shows in human readeable form the files witch size is greater than a value in MB of a given direcroty (no -r)
#
#$1 is the direcroty
#$2 is the minimum size of the file to get sown
find=$(find $1 -maxdepth 1 -mindepth 1 -size +${2}M |  tr ";" "\n")
echo "Nombre,LongitudUsuario,FechaModificacion,FechaAcceso,Tamano,Bloques,Permisos,Ejecutable"
for i in $find ;do
	temp=$(stat --printf="%A" $i | grep w | wc -m)
	if [ 0 -lt "$temp" ]
	then
		echo -e "$(ls $i -A1 | cut -d '	' -f 2)" "\t" "$(echo $USER | wc -m)" "\t" "$((temp-1))" "\t" "$(date -r $i "+ %H:%M:%S")" "\t" "$(stat --printf="%w %X %B %b %A" $i)" " 1"
	else
		echo -e "$(ls $i -A1 | cut -d '	' -f 2)" "\t" "$(echo $USER | wc -m)" "\t" "$((temp-1))" "\t" "$(date -r $i "+ %H:%M:%S")" "\t" "$(stat --printf="%w %X %B %b %A" $i)" " 0"
	fi
done
