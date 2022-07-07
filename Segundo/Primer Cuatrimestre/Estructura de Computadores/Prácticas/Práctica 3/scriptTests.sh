for i in 0 g 1 2; do  
      printf "__OPTIM%1c__%48s\n" $i "" | tr " " "=" 
    for j in $(seq 1 4); do  
      printf "__TEST%02d__%48s\n" $j "" | tr " " "-" 
      rm  popcount 
      gcc popcount.c -o popcount -O$i -D TEST=$j -g 
        ./popcount 
    done 
  done
