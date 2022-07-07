for i in $(seq 1 19); do 
 rm suma3
 gcc -x assembler-with-cpp -D TEST=$i -no-pie suma3.s -o suma3
 printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./suma3
 done 
