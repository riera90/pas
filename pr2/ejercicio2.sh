# !/biirigidon/bash
# this scripts makes a human readeble version of a file containing films
cat $1 | sed -rn -e 's/(^[^\ (Dirigido)(Reparto)()0-9=])/\nTitulo: \1/p' -e  's/^(\([0-9].{8,9})/|-> Fecha de estreno: \1/p' -e 's/^(Dirigida por )(.*)/|-> Director: \2/p' -e 's/^(Reparto:)(.*)/|-> Reparto: \2/p' -e 's/(^[0-9])/|-> Duracion \1/p'
