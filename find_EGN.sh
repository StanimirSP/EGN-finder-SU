[ $# -ge 3 -a $# -le 4 ] || { echo "Usage: $0 <fn> <gender: {m,f}> <birthdate range start> [<birthdate range end>] " >&2; exit 1; }


seq 0 "$(( ($(date --date="${4:-$3}" +%s) - $(date --date="$3" +%s) )/(60*60*24) ))" |\
	xargs -I{} date -d "$3 {} days" "+%Y%m%d" |\
	xargs -I{} -n 1 ./egn_generator {} "$2" "${CBEGIN:-0}" "${CEND:-999}" 2>/dev/null |\
	./egn_sort |\
#	sort -n -k 1.7 |\
	./try_find_egn_parallel.sh "$1"

