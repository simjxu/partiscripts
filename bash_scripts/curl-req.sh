#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Text read from file: $line"
done < "$1"