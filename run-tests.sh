#!/usr/bin/env bash

[ -z "$1" ] || [ -z "$2" ] && echo "Usage: run-tests <start-num> <end-num>" && exit 1

cd tests
for i in `seq $1 $2`
do
    ../vowels test$i < in$i | diff -abq - out$i
done
