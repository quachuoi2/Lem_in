for f in $1/*
do
 touch "$f".new
 cat "$f" -e | cut -d '^' -f1 > "$f".new
 rm "$f"
 mv "$f".new "$f"
done
##remapping maps when transfered between windows/linux/mac