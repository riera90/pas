#!/bin/bash
output="<html><head><title>Listado del directorio ejemploCarpeta/</title></head><body><style type=""text/css"">body { font-family: sans-serif;}</style><h1>Listado del directorio ejemploCarpeta/</h1>"
files=$(find ./)
for it in $files ; do
	output+=$it
done
output+="</body></html>"
echo $output
