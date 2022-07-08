#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct sestruct {
	int a;
	int b;
} ;

int main(int argc, char** argv){ 
    struct timespec cgt1,cgt2; double ncgt;
    int ii, i, X1, X2;
    if (argc<3){	
   	 printf("Faltan argumentos de entrada (N, M)");
    	 exit(-1);
    }
  
    int N = atoi(argv[1]);	
    int M = atof(argv[2]);

    struct sestruct s[N];
    int R[M];

    if(N<9 && M<9)
       for(i=0;i<N;i++){
	s[i].a=-i;
	s[i].b=i;
       } 
    else {
      //se inicializan de forma aleatoria
      //srand(0);   
      srand(time(NULL));
      for(i=0;i<N;i++){
	s[i].a=-rand()%200;
	s[i].b=rand()%100;
      }
    }

    clock_gettime(CLOCK_REALTIME,&cgt1);
	for (ii=0; ii<M;ii++){
		X1=0; X2=0; 
		for(i=0; i<N;i++) X1 += 2*s[i].a + ii;
		for(i=0; i<N;i++) X2 += 3*s[i].b - ii;

		if (X1<X2) {R[ii]=X1;} else {R[ii]=X2;}
	}
    clock_gettime(CLOCK_REALTIME,&cgt2);

    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    // Imprimir resultados
    if(N<10 && M<10){
      for(i=0;i<N;i++){
	printf("s[%d].a=%d \t s[%d].b=%d \n",i,s[i].a,i,s[i].b);
      }
      for(i=0;i<M;i++){
	printf("R[%d]=%d \t",i,R[i]);
      }
      printf("\n");
    }
    else {    
      printf("Tiempo: %11.9f\n", ncgt);
      printf("Elemento 0 y %d de R: %d, %d\n", M-1, R[0], R[M-1]);
    }
}
