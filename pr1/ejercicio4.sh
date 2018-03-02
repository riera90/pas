#!/bin/bash
files=$(ls)
count=$((0))
echo $files
for it in $files ; do
	if [ -f $it ]; then
		count=$((count+1))
	fi
done
echo -e "hay $count ficheros en este directorio"
echo "la lista de usuarios conectados ahora es:"
for it in $(who | cut -d " " -f 1 | tr "" "\n") ; do
	echo $it
done
echo "introdizca un caracter a contar recursivamente en los nombres de los ficheros o directorios:"
clock=5
while [ $((0)) -lt $((clock)) ] ; do
	echo -e "\rtienes $clock segundos para introducit el caracter: \c"
	read -t 1 character
	clock=$((clock-1))
	if [ ! -z "$character" ]; then
		break;
	fi
done
if [ -z "$character" ]; then
	character="a"
	echo "time out"
fi
echo -e "contando el no de $character's que aparecen"
echo $(ls -R | tr -cd "$character" | wc -m)
