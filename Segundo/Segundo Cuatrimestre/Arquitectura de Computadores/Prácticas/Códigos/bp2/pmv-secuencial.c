/**
 * 
 Código para multimplicación secuencial matriz cuadrada por vector: v2 = m * v1 pmv-secuencial.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define VECTOR_GLOBAL
#define VECTOR_DYNAMIC

#ifdef VECTOR_GLOBAL
#define MAX 16375	
double v1[MAX], v2[MAX], m[MAX][MAX]; 
#endif

/**
 * @file  pmv-secuencial.c  
 * @brief multimplicación secuencial matriz cuadrada por vector: v2 = m * v1
 * 
 * @param int n=atoi(argv[1])  número de componentes de los vectores y número de filas y columnas de la matriz
 * @return 0 upon exit success (print tiempo de cálculo de la multiplicación, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *  
 * **Compilación**
 * @code
	gcc  -O2  pmv-secuencial.c -o pmv-secuencial -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S pmv-secuencial.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * pmv-secuencial 8    (para 8 componentes en los vectores)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char** argv){
    unsigned int N;
    struct timespec cgt1,cgt2; double ncgt;
    int i,j;

    if (argc < 2){
        printf("Uso: %s tamaño\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);

    #ifdef VECTOR_GLOBAL
    if (N > MAX)  N = MAX;
    #endif
    
    #ifdef VECTOR_DYNAMIC
    double *v1, *v2, **m;
    v1 = (double*)malloc(N*sizeof(double));
    v2 = (double*)malloc(N*sizeof(double));
    m = (double**)malloc(N*sizeof(double*));
    if ((v1 == NULL) || (v2 == NULL) || (m == NULL)) {
        printf("No hay suficiente espacio para v1, v2 y m \n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        m[i] = (double*)malloc(N*sizeof(double));
        if (m[i] == NULL) {
            printf("No hay suficiente espacio para m \n");
            exit(EXIT_FAILURE);
        }
    }
    #endif

    // Inicializar vector y matriz
    for (i = 0; i < N; i++){
        v1[i] = 0.1*i;
        v2[i] = 0;
        for (j = 0; j < N; j++)
            m[i][j] = i*N+j;
    }

    // Calcular v2 = m * v1
    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            v2[i] += m[i][j] * v1[j];
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    // Imprimir resultados
    if (N < 10){
        printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
        printf("Matriz:\n\t");
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++)
                printf("%8.6f\t ", m[i][j]);
            printf("\n\t");
        }
        printf("\nVector:\n\t");
        for (i = 0; i < N; i++)
            printf("%8.6f ", v1[i]);
        printf("\n\nVector resultado:\n\t");
        for (i = 0; i < N; i++)
            printf("%8.6f ", v2[i]);
        printf("\n");
    } else {
        printf("Tiempo: %11.9f \t Tamaño: %u \t v2[0]: %8.6f \t v2[N-1]: %8.6f \n",ncgt, N, v2[0], v2[N-1]);
    }
    return(0);
}