#!/bin/bash
#this scripts makes a human readeble version of a file containing films
printf "\n*******\n1) Lineas con las duraciones de las peliculas\n\n"
cat $1 | grep -E ^[0-9].*[\ ][0-9].*min
printf "\n*******\n2) Líneas con el pais de las películas\n\n"
cat $1 | grep -E [\-].*[\-]$
printf "\n*******\n3) Solo el pais de las películas\n\n"
cat $1 | grep -E -o [\-].*[\-]$ | grep -E -o [A-Za-z\,\ ]+

p17=$(cat $1 | grep -E -o ^[\(].*[\)] | grep -E -o [0-9]{4} | grep 2017 | wc -l)
p16=$(cat $1 | grep -E -o ^[\(].*[\)] | grep -E -o [0-9]{4} | grep 2016 | wc -l)
printf "\n*******\n4) Hay $p16 pelı́culas del 2016 y $p17 pelı́culas del 2017.\n\n"
printf "\n*******\n5) Eliminar lı́neas vacı́as.\n\n"
# cat $1 | grep -E -v ^$
printf "\n*******\n6) Lı́neas que empiezan la letra E (con o sin espacios antes).\n\n"
cat $1 | grep -E ^[\ ]*E
printf "\n*******\n7) Lı́neas que contienen d, l o t, una vocal y la misma letra.\n\n"
cat $1 | grep -E '([dlt])[aeiou]\1'
printf "\n*******\n8) Lı́neas que contienen ocho aes o más.\n\n"
cat $1 | grep -E '([Aa].*){8,100}'
printf "\n*******\n9) Lı́neas que terminan con tres puntos y no empiezan por espacio.\n\n"
cat $1 | grep -E '^[^\ ].*([\.]){3,3}'
printf "\n*******\n10) Mostrar entre comillas las vocales con tilde.\n\n"
cat $1 | sed -rn 's/([áéíóú])/"\1"/gp'
