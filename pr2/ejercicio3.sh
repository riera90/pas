# !/bin/bash
# this scripts makes a human readeble version of a file containing films
printf "\n######\nlistado de ficheros ocultos\n";ls -a ~/ | grep '^\.'
printf "\n######\ncopia sin lineas vacias\n";echo $(cat $1 | grep -E '[A-Za-z0-9]') > $1.sin_lineas_vacias
printf "\n######\nPID's\n"; ps -ux | sed -rn 's/(^[A-Za-z]*)\ *([0-9]*)\ *([0-9\.]*)\ *([0-9\.]*\ *[0-9]*\ *[0-9]*)\ *([A-Za-z0-9\?\/]*)\ *([A-Za-z]*)\ *([0-9A-Za-z\:]*)\ *([0-9\:]*)\ *([A-Za-z\/\-]*)/PID: "\2" Hora: "\7" Ejecutable: \9/p'
