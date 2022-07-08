/**
 * 
 Cláusula lastprivate con for
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
 * @file  lastprivate-clause.c 
 * @brief _Parte del código de suma paralalela_
 * @return 0 upon exit success (print la variable suma dentro y fuera del <tt>parallel</tt>)
 *  
 * **Objetivo**
 * 
 * El código usa:
 * 
 * - Directivas <tt>parallel, for</tt> 
 * - Cláusulas <tt>lastprivate</tt> 
 * - Funciones <tt>omp_get_thread_num()</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o lastprivate-clause lastprivate-clause.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * lastprivate-clause 
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main()
{
   int i, n = 7;
   int a[n],v;

   for (i=0; i<n; i++)
      a[i] = i+1;

#pragma omp parallel for lastprivate(v)
   for (i=0; i<n; i++)
   {
       v = a[i];
       printf("Hebra %d v=%d / ",
             omp_get_thread_num(),v);
   } 

   printf("\nFuera de la construcción 'parallel for' v=%d\n",v); 
   return(0);
}
