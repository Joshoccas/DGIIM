for i in $(seq 1 19); do 
 rm media64
 gcc -x assembler-with-cpp -D TEST=$i -no-pie media64.s -o media64
 printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./media64
 done 
