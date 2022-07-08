/**
 * 
 * Ejemplo que ilustra el uso de <tt>target teams distribute parallel for</tt> y relaciona equipos y hebras con el hardware de la GPU: omp_offload.c
 * 
 */

#include <stdlib.h> // funciones atoi(),rand(), srand(), malloc() y free()
#include <stdio.h>  // función printf() 
#include <omp.h>    // función omp_get_num_devices()
#define MAX 33554432 //=2^25
int inf[MAX][4]; /**< Cada fila 4 elementos: threads, total threads, team, total teams */
/**
 * @file  omp_offload.c 
 * @brief _Reparto de trabajo entre equipos y entre los hebras/hilos de un equipo, uso de <tt>target teams distribute parallel for</tt>_
 * @author Mancia Anguita López
 * 
 * @param N=atoi(argv[1])  longitud de los vectores x, y, z
 * @param a=atoi(argv[2])  Alpha
 * @param b=atoi(argv[3])  Beta
 * @return 0 upon exit success (print tiempos y z = Alpha * x + Beta * y )
 * 
 * **Objetivo**
 * 
 * El código ilustra:
 * 
 * - Directivas <tt>target, distribute, parallel, for</tt> 
 * 
 * - Cláusulas <tt>num_teams(), thread_limit()</tt>
 * 
 * - La relación entre el número de equipos (teams) y de hilos en un equipo (threads/team) con el hardware de la GPU
 * 
 *
 * **Compilación en atcgrid4:**
 * @code
 * sbatch -Aaapt -paapt -watcgrid4 --wrap "nvc -O2 -openmp -mp=gpu omp_offload.c -o omp_offload"
 * @endcode
 * 
 *  **Ejecución en atcgrid4:**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun -Aaapt -paapt -watcgrid4 omp_offload 49152 2 32  //N=49152 filas matrix inf[][4], nº de equipos (nteams=2) y máximo hilos por equipo (mthreads=32)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
    double t1 = 0.0, t2 = 0.0;

    if (argc < 4)
    {
        printf("Faltan argumentos de entrada (n. filas inf[][4], nteams, mthreads)");
        exit(-1);
    }

    int N = atoi(argv[1]);
    int nteams = atoi(argv[2]);
    int mthreads = atoi(argv[3]);
    printf("Target device: %i \n", omp_get_num_devices());

    t1 = omp_get_wtime();

#pragma omp target teams distribute parallel for map(from: inf[:N][4]) num_teams(nteams) thread_limit(mthreads) 
    for (int i = 0; i < N; i++)
    {
        //printf("*** Tarea (iteración) %d ejecutada por el thread %d de %d (max threads=) del team %d (de %d). \n",
        //     i, omp_get_thread_num(), omp_get_num_threads(), omp_get_team_num(), omp_get_num_teams());
        inf[i][0] = omp_get_thread_num();
        inf[i][1] = omp_get_num_threads(); //El nº de threads cambia entre ejecuciones, aunque no cambie la entrada
        inf[i][2] = omp_get_team_num();
        inf[i][3] = omp_get_num_teams();
    }

    t2 = omp_get_wtime();
    printf("Tiempo:%11.9f\t \n", t2 - t1);
    for (int j = 0; j < N; j++)
        printf("Iteracción %d, en thread %d/%d del team %d/%d\n", j, inf[j][0], inf[j][1], inf[j][2], inf[j][3]);
    return 0;
}
