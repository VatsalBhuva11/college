#!/bin/bash

read -p "Enter n: " n
i=0
while [ $i -lt $n ]
do
	j=1
	while [ $j -le `expr $n - $i` ]
	do
		echo -n "$j "
		j=`expr $j + 1`
	done
	j=`expr $j - 1`
	k=1
	while [ $k -le `expr 2 \* $n - 2 \* $j` ]
	do
		echo -n "* "
		k=`expr $k + 1`
	done
	k=`expr $n - $i`
	while [ $k -ge 1 ]
	do
		echo -n "$k "
		k=`expr $k - 1`
	done
	echo
	i=`expr $i + 1`
done

