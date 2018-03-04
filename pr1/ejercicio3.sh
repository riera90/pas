#!/bin/bash
#this script organizes the files by size and moves the files to an acording directory
if [ "$1" == $"" ]; then
	echo "error"
else
	dir=$1
fi

if [ "$2" == $"" ] ; then
	low_limit=$((10000))
else
	low_limit=$2
fi
if [ "$3" == $"" ] ; then
	top_limit=$((100000))
else
	top_limit=$3
fi
#deletes the directories if created
if [ -d "$dir""/small" ]; then
	echo "deleting foldet 'small'"
	rm -r "$dir"/small
fi
if [ -d "$dir""/medium" ]; then
	echo "deleting foldet 'medium'"
	rm -r "$dir"/medium
fi
if [ -d "$dir""/big" ]; then
	echo "deleting foldet 'big'"
	rm -r "$dir"/big
fi
mkdir "$dir"/small
mkdir "$dir"/medium
mkdir "$dir"/big

echo -e "dir: $dir \t low: $low_limit \t top: $top_limit"
files=$(ls $dir)
echo $files
for it in $files ; do
	origin="$dir""/""$it"
	if [ -d $origin ]; then
		echo -e "$it is a directory , doing nothing"
	else
		echo $origin
		size=$(stat $origin --printf="%s")
		if [ $((size)) -lt $((low_limit)) ]; then
			#small
			echo -e "$it es pequeño"
			mv $origin $dir"/small/"$it
		else
			if [ $((size)) -lt $((top_limit)) ]; then
				#big
				echo -e "$it es grande"
				mv $origin $dir"/big/"$it
			else
				#med
				echo -e "$it es mediano"
				mv $origin "$dir""/medium/""$it"
			fi
		fi
	fi
done
