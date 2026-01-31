#!/bin/bash

TEST_DIRS=("test/Lab 0x02" "test/Lab 0x04")

if [ ! -f "./movfuscator" ]; then
    exit 1
fi

for dir in "${TEST_DIRS[@]}"; do
    for file in "$dir"/ex0x*.s; do
        [ -e "$file" ] || continue
        
        ./movfuscator "$file"
        
        if [ $? -eq 0 ]; then
            echo "SUCCESS: $(basename "$file")"
        else
            echo "FAILED: $(basename "$file")"
        fi
    done
done