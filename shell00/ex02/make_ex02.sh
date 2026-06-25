#!/bin/sh
mkdir -p test0
touch -t 06012047 test0
chmod 715 test0

printf "Hell" > test1
touch -t 06012146 test1
chmod 714 test1

mkdir -p test2
touch -t 06012245 test2
chmod 504 test2

printf "1" > test3
ln test3 test5
touch -t 06012344 test3
chmod 404 test3

printf "42" > test4
touch -t 06012343 test4
chmod 641 test4

ln -s test0 test6
touch -h -t 06012220 test6

tar -cf exo2.tar test0 test1 test2 test3 test4 test5 test6
