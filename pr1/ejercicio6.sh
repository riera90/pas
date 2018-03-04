#!/bin/bash
#this sctipt makes an html human readeable list of all the
#recursive directories of a given bvase directory
function explore_directory {
	if [ ${#output} -gt 1000 ]; then
		echo $output >> $dir.html
		output=""
	fi
	output+="<ul>"
	files=$(find $1 -maxdepth 1 -mindepth 1)
	directories=""
	for it in $files ; do
		if [ -d $it ]  ; then directories+=$it" "; else output+="<li>$it</li>"; fi
	done
	for directory in $directories ; do
		output+="<li><strong>$directory</strong></li>"
		explore_directory $directory
		output+="</ul>";
	done
}
output="<html><head><title>Listado del directorio ${1}</title></head><body><style type=""text/css"">body { font-family: sans-serif;}</style><h1>Listado del directorio ${1}</h1>"
dir=$(basename $1)
echo -e "<$dir>"
if [ -f "$dir.html" ] ; then rm "$dir.html" ; touch $dir.html ; fi
explore_directory $1
output+="</body></html>"
echo $output >> $dir.html
