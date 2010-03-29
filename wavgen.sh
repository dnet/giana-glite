#!/bin/bash

gcc wavgen.c -o wavgen -Wall -DSRATE=$1 -lm &> compile.log

if [ $? -ne 0 ]
then
	echo "Compile error"
	exit
fi

./wavgen $2 >wavdata.bin
