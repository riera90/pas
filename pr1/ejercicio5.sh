#!/bin/bash
#the script makes a backup of the files in the argument
#the file will be named copia-<user>-<date form 1970 in sec>
#stored in the home directory
#if there are backups the bukups older of 200 sec will be deleted
tar cf "copia-$(whoami)-$(date +%s).tar" $@
if [ ! -d ~/copia ]; then
	mkdir ~/copia
fi
mv "copia-$(whoami)-$(date +%s).tar" ~/copia
files=$(ls ~/copia)
for it in $files ; do
	if [ $(stat --format="%Y" ~/copia/$it) -lt $(($(date +%s) - 200)) ] ; then
		echo "deleting!"
		rm ~/copia/$it
	fi
done
