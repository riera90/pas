#!/bin/bash
#this script prints a human readeable version of various files of /proc
#ejercicio5.sh
cpu=$(cat /proc/cpuinfo | sed -rn 's/model name	: (.*)/modelo de procesador: \1/p')
cores="Numero de hilos máximo: $(printf "$cpu\n" | wc -l)"
cpu=$(echo "$cpu\n" | cut -d '
' -f 1)
megahercios="$(cat /proc/cpuinfo | sed -rn 's/cpu MHz		: (.*)/megahercios: \1/p' | cut -d '
' -f 1) Mhz"

vendor=$(cat /proc/cpuinfo | sed -rn 's/vendor_id	: (.*)/vendor: \1/p' | cut -d '
' -f 1)

cache=$(cat /proc/cpuinfo | sed -rn 's/^cache size	: (.*)/tamaño de cache: \1/p' | cut -d'
' -f 1)


printf "$cpu\n"
printf "$cores\n"
printf "$megahercios\n"
printf "$cache\n"
printf "$vendor\n"


printf "\npuntos de montaje:\n"
cat /proc/mounts | sed -rn 's/^[a-z]*\ *([a-z/]*)\ *([a-z]*)\ *[a-z]*,[a-z]*,([a-z]*),[a-z]*.*/-> punto de montaje: \1,\t Dispositivo: \3, \ttipo de dispositivo: \2/p' | sort -r

printf "\nparticiones y numero de bloques:\n"
cat /proc/partitions | sed -rn 's/\ \ \ [0-9]*\ *[0-9]*\ *([0-9]*)\ *([0-9a-z]*)/-> particion: \2,\t numero de bloques: \1/p'
