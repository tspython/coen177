#!/bin/bash

for file in file1.txt file2.txt file3.txt file4.txt 
do
    for buffer in 100000
    do
        for thread in 2 64
        do
            echo "Step5 $file $buffer $thread"
            time ./Step5 $file $buffer $thread
            echo " "
        done
    done
done
