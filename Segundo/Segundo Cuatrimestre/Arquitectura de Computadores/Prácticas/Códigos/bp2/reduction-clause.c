/**
 * 
 Cláusula reductions
 *
 **/

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

/**
 * @file  reduction-clause.c 
 * @brief _Parte del código de suma paralalela_
 * @param int n=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print la suma de los componentes de un vector fuera del <tt>parallel</tt>)
 *  
 * **Objetivo**
 * 
 * El código usa:
 * 
 * - Directivas <tt>parallel, for</tt> 
 * - Cláusulas <tt>reduction default private shared </tt> 
 * - Funciones <tt>omp_get_thread_num()</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o reduction-clause reduction-clause.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * reduction-clause   16  (para 16 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char **argv)
{
   int i, n=20;
   int a[n],suma=0;
   if(argc < 2)     {
      fprintf(stderr,"[ERROR]-Falta iteraciones\n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>20) {n=20; printf("n=%d",n);}

   for (i=0; i<n; i++) {
      a[i] = i; 
   }
 
   #pragma omp parallel for default(none) private(i) shared(a,n,suma)
   for (i=0; i<n; i++){
      #pragma omp atomic
      suma += a[i];
   } 

   printf("Tras 'parallel' suma=%d\n",suma);
   return(0);
}
