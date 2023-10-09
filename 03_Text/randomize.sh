#!/usr/bin/env bash
exit_handler() {
  trap - EXIT
  test -r "$INPFILE" && rm -vf "$INPFILE"
  test -r "$CHARFILE" && rm -vf "$CHARFILE"
}

trap exit_handler EXIT HUP INT QUIT PIPE TERM

if [ "$#" -gt "0" ]; then
    ospeed=$1
else
    ospeed=0.0
fi

INPFILE="`mktemp`"
CHARFILE="`mktemp`"
NEWCHARFILE="`mktemp`"
IFS=""

while read input; do
    echo $input >> "$INPFILE"
done

i=0
j=0
while read -N1 char; do
    if [ "$char" = $'\n' ]; then
        i=$(( $i + 1 ))
        j=0
    fi
    echo $char, $i, $j >> "$CHARFILE"
    j=$(( $j + 1))
done < "$INPFILE"

tput clear
tput cup 0 0

shuf "$CHARFILE" >> "$NEWCHARFILE"
IFS=", "
while read char pos_i pos_j; do
    tput cup "$pos_i" "$pos_j"
    echo "$char"
    sleep "$ospeed"
done < "$NEWCHARFILE"

newline=$(wc -l < "$INPFILE")
tput cup "$newline" 0
