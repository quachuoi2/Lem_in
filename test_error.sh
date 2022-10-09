RESULT_FILE=./error_result

if test -f "$RESULT_FILE"; then
	printf "result:\n" > "$RESULT_FILE"
else
	touch "$RESULT_FILE"
	printf "result:\n" > "$RESULT_FILE"
fi
for f in $1*
do
	printf "$f:\n" | rev | cut -d '/' -f 1 | rev >> "$RESULT_FILE"
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valout ./a.out < "$f" >> "$RESULT_FILE"
	grep "in use" valout >> "$RESULT_FILE"
	grep "ERROR SUMMARY" valout >> "$RESULT_FILE"
	printf "\n" >> "$RESULT_FILE"
done