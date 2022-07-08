/* daxpy.c 
 Double precision-real Alpha x Plus y: z = alpha * x + y
 
 Para compilar usar (-lrt: real time library):  
	gcc  -O2  daxpy.c -o daxpy -lrt

 Para ejecutar use: daxpy longitud alpha
		
*/ 

#include <stdlib.h>	// biblioteca con funciones atoi(),rand(), srand(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la función printf()
#include <time.h>	// biblioteca donde se encuentra la función clock_gettime() 
//#define VECTOR_LOCAL	
#define VECTOR_GLOBAL 
//#define VECTOR_DYNAMIC
#define VECTOR_GLOBAL 

#ifdef VECTOR_GLOBAL
#define MAX 33554432	//=2^25
  
double x[MAX], y[MAX], z[MAX]; 
#endif
 
int main(int argc, char** argv){ 
  
  int i; 

  struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<3){	
    printf("Faltan argumentos de entrada (n. componentes, alpha)");
    exit(-1);
  }
  
  int N = atoi(argv[1]);	// Máximo N =2^32-1=4294967295 (sizeof(int) = 4 B)
  double alpha = atof(argv[2]);
  #ifdef VECTOR_LOCAL
  double x[N], y[N], z[N];   // Tamaño variable local en tiempo de ejecución ...
				// disponible en C a partir de C99 
  #endif
  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif
  #ifdef VECTOR_DYNAMIC
  float *x, *y, *z;
  x = (float*) malloc(N*sizeof(float));// malloc necesita el tamaño en bytes
  y = (float*) malloc(N*sizeof(float));
  z = (float*) malloc(N*sizeof(float));
  #endif
 
  //Inicializar vectores  
  if (N < 9)
    for (i = 0; i < N; i++)
    {
      x[i] = N * 0.1 + i * 0.1; y[i] = N * 0.1 - i * 0.1;
    }
  else
  {
    //srand(time(0));
    for (i = 0; i < N; i++)
    {
      x[i] = drand48(); 
      y[i] = drand48(); 
    }
  }
 
  clock_gettime(CLOCK_REALTIME,&cgt1);
  //Cálculos daxpyz 
  for(i=0; i<N; i++) 
    z[i] = alpha*x[i] + y[i]; 
 
  clock_gettime(CLOCK_REALTIME,&cgt2);
  ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

  //Imprimir resultado de la suma y el tiempo de ejecución
  if (N<11) { 
  printf("Tiempo:%11.9f\t / Tamaño Vectores:%d\n",ncgt,N); 
  for(i=0; i<N; i++) 
    printf("/ alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,alpha,x[i],y[i],z[i]); 

  } else {
    printf("Tiempo:%11.9f\t / Tamaño Vectores:%d\t/ alpha*x[0]+y[0]=z[0](%8.6f*%8.6f+%8.6f=%8.6f) / / alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n",
           ncgt,N,alpha,x[0],y[0],z[0],N-1,N-1,N-1,alpha,x[N-1],y[N-1],z[N-1]); 
  }

  #ifdef VECTOR_DYNAMIC
  free(x); // libera el espacio reservado para v1
  free(y); // libera el espacio reservado para v2
  free(z); // libera el espacio reservado para v3
  #endif
  return 0; 
}
