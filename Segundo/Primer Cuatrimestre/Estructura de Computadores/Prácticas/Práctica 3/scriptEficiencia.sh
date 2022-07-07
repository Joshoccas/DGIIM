#!/bin/bash

for i in 0 g 1 2; do  
      printf "__OPTIM%1c__%48s\n" $i "" | tr " " "=" 
      rm  popcount
      gcc popcount.c -o popcount -O$i -D TEST=0 
    for j in $(seq 0 10); do  
      echo $j; ./popcount
    done | pr -11 -l 22 -w 80 -J
  done
