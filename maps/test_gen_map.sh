RESULT_FILE=./gen_map_result
LEM_IN_BINARY=../lem-in

if test -f "$RESULT_FILE";
then
	printf "result:\n" > "$RESULT_FILE"
else
	touch "$RESULT_FILE"
	printf "result:\n" > "$RESULT_FILE"
fi

for f in $1/*
do
	printf "$f:\n" | rev | cut -d '/' -f 1 | rev >> "$RESULT_FILE"
	printf "expected:" >> "$RESULT_FILE"
	head -n 2 "$f"  | grep "required" | cut -d : -f2 >> "$RESULT_FILE"
	printf "got: " >> "$RESULT_FILE"

	#use leaks to check for memleaks
	leaks -atExit -quiet -- "$LEM_IN_BINARY" -l -q < "$f" >> "$RESULT_FILE"

	#use valgrind instead (add # to leaks and remove for the next 3 lines)
	# valgrind --leak-check=full --show-leak-kinds=all --log-file=valout "$LEM_IN_BINARY" -l -q < "$f" >> "$RESULT_FILE"
	# grep "in use" valout >> "$RESULT_FILE"
	# grep "ERROR SUMMARY" valout >> "$RESULT_FILE"
	printf "\n" >> "$RESULT_FILE"
done
