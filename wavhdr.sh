#!/bin/bash

gcc wavhdr.c -o wavhdr -Wall -DSRATE=$1 &> compile.log

if [ $? -ne 0 ]
then
	echo "Compile error"
	exit
fi

./wavhdr `stat --format="%s" wavdata.bin` >output.wav
cat wavdata.bin >>output.wav
