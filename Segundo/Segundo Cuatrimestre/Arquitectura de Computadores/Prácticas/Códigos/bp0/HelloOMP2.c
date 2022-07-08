/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP2.c –o HelloOMP2
 * 
 */

#include <stdio.h>
#include <omp.h>

int main(void) {

#pragma omp parallel
  printf("(%d:!!!Hello)", 
           omp_get_thread_num());
  printf("\n");
#pragma omp parallel
  printf("(%d:world!!!)", 
           omp_get_thread_num());

return(0);

}
