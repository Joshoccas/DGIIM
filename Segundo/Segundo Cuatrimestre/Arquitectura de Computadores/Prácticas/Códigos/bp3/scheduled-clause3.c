#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
 
    #pragma omp parallel for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
    	if(i == 0){
    	
    		int modifier;
    		omp_sched_t kind;
    		omp_get_schedule(&kind,&modifier);
    		
    		printf("REGIÓN PARALELA ANTES DE MODIFICAR\n");
    		printf("Dinámica (true 0, false 1): %d\n",omp_get_dynamic());
    		printf("Nºthreads: %d\n",omp_get_max_threads());
    		printf("Kind (Static 1, Dynamic 2, Guided 3): %d\n", kind);
    		printf("Chunk: %d\n\n", modifier);
    		
    		omp_set_dynamic(5);
    		omp_set_num_threads(6);
    		omp_set_schedule(3,2);
    		omp_get_schedule(&kind,&modifier);
    		
    		printf("REGIÓN PARALELA DESPUÉS DE MODIFICAR\n");
    		printf("Dinámica (true 0, false 1): %d\n",omp_get_dynamic());
    		printf("Nºthreads: %d\n",omp_get_max_threads());
    		printf("Kind (Static 1, Dynamic 2, Guided 3): %d\n", kind);
    		printf("Chunk: %d\n\n", modifier);
    	}
        suma = suma + a[i];
        // printf(" thread %d suma a[%d]=%d suma=%d \n",
              // omp_get_thread_num(),i,a[i],suma);
    }

    printf("Fuera de 'parallel for': \n");
    
    int modifier;
    omp_sched_t kind;
    omp_get_schedule(&kind,&modifier);
    
    
    printf("REGIÓN SECUENCIAL ANTES DE MODIFICAR\n");
    printf("Dinámica (true 0, false 1): %d\n",omp_get_dynamic());
    printf("Nºthreads: %d\n",omp_get_max_threads());
    printf("Kind (Static 1, Dynamic 2, Guided 3): %d\n", kind);
    printf("Chunk: %d\n\n", modifier);
    		
    omp_set_dynamic(4);
    omp_set_num_threads(4);
    omp_set_schedule(2,1);
    omp_get_schedule(&kind,&modifier);
    
    		
    printf("REGIÓN SECUENCIAL DESPUÉS DE MODIFICAR\n");
    printf("Dinámica (true 0, false 1): %d\n",omp_get_dynamic());
    printf("Nºthreads: %d\n",omp_get_max_threads());
    printf("Kind (Static 1, Dynamic 2, Guided 3): %d\n", kind);
    printf("Chunk: %d\n\n", modifier);
    
}
