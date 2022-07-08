/**
 * 
 Directiva critical
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
 * @file  critical.c 
 * @brief #### Se suman los elementos de una lista. El hilo 0 imprime el resultado fuera de <tt>parallel</tt> ####
 * 
 * @param N=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print la suma y el identificador del hilo que imprime )
 *  
 * **Objetivo**
 * 
 * El código ilustra:
 * 
 * - Directivas <tt>parallel, for, critical</tt> 
 * 
 * - Cláusulas <tt>private </tt>
 * 
 * - La distribución de las iteraciones del bucle entre los hilos usando <tt>schedule(static)</tt>
 * 
 *
 * **Compilación**
 * @code
 * gcc -O2 -fopenmp -o critical critical.c
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * critical 8    (para 8 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
   int i, n=20;
   int a[n],suma=0,sumalocal;
   if(argc < 2)     {
      fprintf(stderr,"\n[ERROR] - Falta iteraciones\n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++) {
      a[i] = i; 
   }
 
#pragma omp parallel private(sumalocal) shared(a,suma,n)
{  sumalocal=0;
   #pragma omp for private(i) schedule(static)
   for (i=0; i<n; i++)
   {
       sumalocal += a[i];
       printf(" Hebra %d suma de a[%d]=%d sumalocal=%d \n",
             omp_get_thread_num(),i,a[i],sumalocal);
   } 
   //#pragma omp critical (x)
       suma += sumalocal;
}  
   printf("Fuera de 'parallel for' suma=%d\n",suma); 
   return(0);
}
