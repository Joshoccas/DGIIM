/**
 * 
 Código para multimplicación secuencial de matrices: m3 = m1 * m2 pmm-secuencial.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define VECTOR_GLOBAL
#define VECTOR_DYNAMIC

#ifdef VECTOR_GLOBAL
#define MAX 16375	
double m1[MAX][MAX], m2[MAX][MAX], m3[MAX][MAX]; 
#endif

/**
 * @file  pmv-secuencial.c  
 * @brief multimplicación secuencial de matrices: m3 = m1 * m2
 * 
 * @param int n=atoi(argv[1])  número de filas y columnas de las matrices
 * @return 0 upon exit success (print tiempo de cálculo de la multiplicación, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *  
 * **Compilación**
 * @code
	gcc  -O2  pmm-secuencial.c -o pmm-secuencial -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S pmm-secuencial.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * pmm-secuencial 8    (para 8 componentes en los vectores)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char** argv){
    unsigned int N;
    struct timespec cgt1,cgt2; double ncgt;
    int i,j,k;

    if (argc < 2){
        printf("Uso: %s tamaño\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);

    #ifdef VECTOR_GLOBAL
    if (N > MAX)  N = MAX;
    #endif
    
    #ifdef VECTOR_DYNAMIC
    double **m1, **m2, **m3;
    m1 = (double**)malloc(N*sizeof(double*));
    m2 = (double**)malloc(N*sizeof(double*));
    m3 = (double**)malloc(N*sizeof(double*));
    if ((m1 == NULL) || (m2 == NULL) || (m3 == NULL)) {
        printf("No hay suficiente espacio para m1, m2 y m3 \n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        m1[i] = (double*)malloc(N*sizeof(double));
        if (m1[i] == NULL) {
            printf("No hay suficiente espacio para m1 \n");
            exit(EXIT_FAILURE);
        }
        m2[i] = (double*)malloc(N*sizeof(double));
        if (m2[i] == NULL) {
            printf("No hay suficiente espacio para m2 \n");
            exit(EXIT_FAILURE);
        }
        m3[i] = (double*)malloc(N*sizeof(double));
        if (m3[i] == NULL) {
            printf("No hay suficiente espacio para m3 \n");
            exit(EXIT_FAILURE);
        }
    }
    #endif

    // Inicializar vector y matriz
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            m1[i][j] = i*N + j;
            m2[i][j] = 0.1*(j*N + i);
            m3[i][j] = 0;
        }
    }

    // Calcular m3 = m1 * m2
    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    // Imprimir resultados
    if (N < 10)
    {
        printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
        printf("\n Matriz 1 (m1):\n");
        for (int i = 0; i < N; i++)
        {
            printf("\t");
            for (int j = 0; j < N; j++)
            {
                printf("%8.6f\t ", m1[i][j]);
            }
            printf("\n");
        }
        printf("\n Matriz 2 (m2):\n");
        for (int i = 0; i < N; i++)
        {
            printf("\t");
            for (int j = 0; j < N; j++)
            {
                printf("%8.6f\t ", m2[i][j]);
            }
            printf("\n");
        }
        printf("\n Matriz resultado (m3):\n");
        for (int i = 0; i < N; i++)
        {
            printf("\t");
            for (int j = 0; j < N; j++)
            {
                printf("%8.6f\t ", m3[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else
    {
        printf("Tiempo: %11.9f \t Tamaño: %u \t m3[0][0]: %8.6f \t m3[N-1][N-1]: %8.6f \n", ncgt, N, m3[0][0], m3[N-1][N-1]);
    }
    return(0);
}
