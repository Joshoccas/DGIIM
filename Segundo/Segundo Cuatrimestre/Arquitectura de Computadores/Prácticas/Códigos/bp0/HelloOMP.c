/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP.c –o HelloOMP
 * 
 */

#include <stdio.h>
#include <omp.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

int main(void) {

int ID;
//omp_set_num_threads(6);
#pragma omp parallel
{
  ID = omp_get_thread_num();
  printf("Hello(%d)",ID);
  printf("World(%d)\n",ID);
}

return(0);

}
