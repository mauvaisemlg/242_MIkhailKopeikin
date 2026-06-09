#!/bin/bash

sum()
{
    local res=0
    local x

    for x in "$@"; do
        res=$(expr "$res" + "$x" 2>/dev/null)

        if [ $? -ne 0 ]; then
            echo 0
            return
        fi
    done

    echo "$res"
}

read -r -a first
read -r -a second

a=$(sum "${first[@]}")
b=$(sum "${second[@]}")

if [ "$a" = "$b" ]; then
    echo "Equal"
else
    echo "Not equal"
fi
