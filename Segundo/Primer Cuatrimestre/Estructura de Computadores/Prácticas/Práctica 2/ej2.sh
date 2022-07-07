for i in $(seq 1 6); do 
 rm suma2
 gcc -x assembler-with-cpp -D TEST=$i -no-pie suma2.s -o suma2 
 printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./suma2
 done 
