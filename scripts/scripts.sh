#!/usr/bin/env bash

echo "1 Print even numbers"

for ((i=100; i <= 1000; i += 2))
do
    echo -n "$i "
done

echo -e "\n"
echo "2 Init array"

declare -a array

for i in {0..25}
do
    array[$i]=$i
done

for index in ${!array[*]}
do
    echo -n "${array[$index]} "
done

echo -e "\n"
echo "3 math expression"

res=$(echo "100 + 0.5" | bc)

echo "100 + 0.5 = $res"

echo
echo "4 Create file"

FILENAME="Linux"

if [ -f "./$FILENAME" ]
then
    echo "course"
else
    echo "very easy"
    echo "course is easy" >> "./$FILENAME"
fi