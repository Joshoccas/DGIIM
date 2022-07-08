/**
 * 
 Directiva master
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

/**
 * @file  master.c 
 * @brief #### Se suman los elementos de una lista. El hilo 0 imprime el resultado usando <tt>master</tt> dentro de <tt>parallel</tt> ####
 * 
 * @param int n=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print la suma y el identificador del hilo que imprime )
 *  
 * **Objetivo**
 * 
 * El código ilustra:
 * 
 * - Directivas <tt>parallel, for, barrier, atomic, master</tt> 
 * 
 * - Cláusulas <tt>private </tt>
 * 
 * - La distribución de las iteraciones del bucle entre los hilos usando <tt>schedule(static)</tt>
 * 
 *
 * **Compilación**
 * @code
 * gcc -O2 -fopenmp -o master master.c
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * master 8    (para 8 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
   int i, n=20, tid;
   int a[n],suma=0,sumalocal;
   if(argc < 2)     {
      fprintf(stderr,"\n[ERROR] - Falta iteraciones\n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++) {
      a[i] = i; 
   }
 
#pragma omp parallel private(sumalocal,tid) 
{  sumalocal=0;
   tid=omp_get_thread_num();
   #pragma omp for schedule(static) 
   for (i=0; i<n; i++)
   {
       sumalocal += a[i];
       printf(" Hebra %d suma de a[%d]=%d sumalocal=%d \n",
             omp_get_thread_num(),i,a[i],sumalocal);
   } 
   #pragma omp atomic 
       suma += sumalocal;
   #pragma omp barrier
   #pragma omp master
	printf("Thread master=%d imprime suma=%d\n",tid,suma);
}  
   return(0);
}
