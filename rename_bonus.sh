#!/bin/bash
# Save this as rename_bonus.sh

echo "Renaming .c files..."
find ./src -name "*.c" | while read file; do
    dir=$(dirname "$file")
    base=$(basename "$file" .c)
    new_name="$dir/${base}_bonus.c"
    mv "$file" "$new_name"
    echo "Renamed: $file -> $new_name"
done

echo "Renaming .h files..."
find ./includes -name "*.h" 2>/dev/null | while read file; do
    dir=$(dirname "$file")
    base=$(basename "$file" .h)
    new_name="$dir/${base}_bonus.h"
    mv "$file" "$new_name"
    echo "Renamed: $file -> $new_name"
done

echo "Updating Makefile..."
# Update all .c references in Makefile
sed -i 's/\.c/_bonus.c/g' Makefile

echo "Done! All files renamed with _bonus suffix and Makefile updated."