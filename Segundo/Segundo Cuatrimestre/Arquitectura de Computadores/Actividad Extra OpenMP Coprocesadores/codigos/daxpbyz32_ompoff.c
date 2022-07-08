/**
 * 
 * Ejemplo que ilustra el uso de <tt>target enter data/target exit data</tt>: daxpbyz32_ompoff.c
 * 
 */

#include <stdlib.h> // funciones atoi(),rand(), srand(), malloc() y free()
#include <stdio.h>  // función printf() 
#include <omp.h>    // función omp_get_num_devices()

/**
 * @file  daxpbyz32_ompoff.c 
 * @brief _Simple precision-real Alpha x Plus Beta y (z = Alpha * x + Beta * y) con OpenMP offload, usa <tt>target enter data/target exit data</tt>_
 * @author Mancia Anguita López
 * 
 * @param N=atoi(argv[1])  longitud de los vectores x, y, z
 * @param a=atoi(argv[2])  Alpha
 * @param b=atoi(argv[3])  Beta
 * 
 * **Objetivo**
 * 
 * El código ilustra el uso de:
 * 
 * - <tt>target enter data, target exit data, target update</tt>
 * - El cálculo se realiza con dos bucles independientes para ilustrar el uso de <tt>target update</tt> 
 * - Tiempos que suponen las transferencias.
 * 
 * - <tt>target, distribute, parallel, for</tt> 
 * 
 * **Compilación en atcgrid4:**
 * @code
 * sbatch -Aaapt -paapt -watcgrid4 --wrap "nvc -O2 -openmp -mp=gpu daxpbyz32_ompoff.c -o daxpbyz32_ompoff"
 * @endcode
 * 
 *  **Ejecución en atcgrid4:**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun -Aaapt -paapt -watcgrid4 daxpbyz32_ompoff 49152 2 3  //N=49152 es la longitud de los vectores, Alpha=2 y Beta=3
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
    int i, N;
    double t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0;
    float *x, *y, *z, a, b, p;

    if (argc < 4)  {
        printf("Faltan argumentos de entrada (n. componentes, alpha, beta)");
        exit(-1);
    }

    N = atoi(argv[1]);
    a = atof(argv[2]);
    b = atof(argv[3]);
    printf("Target device: %i \n", omp_get_num_devices());

    t0 = omp_get_wtime();
    x = (float *)malloc(N * sizeof(float));
    y = (float *)malloc(N * sizeof(float));
    z = (float *)malloc(N * sizeof(float));
    if ((x == NULL) || (y == NULL) || (z == NULL))
    {
        printf("Error malloc\n");
        exit(1);
    }

    for (i = 0; i < N; i++)
        x[i] = N * 0.1 + i * 0.1;

    t1 = omp_get_wtime();

    p = a;

#pragma omp target enter data map(to: N, p, x[:N]) map(alloc: z[:N], y[0:N])

    t2 = omp_get_wtime();

#pragma omp target teams distribute parallel for
    for (int i = 0; i < N; i++)
        z[i] = p * x[i];

    t3 = omp_get_wtime();

    p = b;

    for (i = 0; i < N; i++)
        y[i] = N * 0.1 - i * 0.1;

    t4 = omp_get_wtime();

#pragma omp target update to(p, y[:N])

    t5 = omp_get_wtime();

#pragma omp target teams distribute parallel for
    for (int i = 0; i < N; i++)
        z[i] = z[i] + p * y[i];

    t6 = omp_get_wtime();

#pragma omp target exit data map(delete: N, p, x[:N], y[0:N]) map(from: z[:N])

    t7 = omp_get_wtime();

    if (N < 11)
    {
        printf(" * \tTiempo: ((Reserva+inicialización) host %11.9f) + (target enter data: %11.9f) + (target1 %11.9f) + (host actualiza %11.9f) + (target data update %11.9f) + (target2 %11.9f) + (target exit data %11.9f)= %11.9f\t / Tamaño Vectores:%d\n",
               t1 - t0, t2 - t1, t3 - t2, t4 - t3, t5 - t4, t6 - t5, t7 - t6, t7 - t0, N);
        for (i = 0; i < N; i++)
            printf("/ alpha*x[%d]+beta*y[%d]=z[%d](%8.6f*%8.6f+%8.6f*%8.6f=%8.6f) /\n",
                   i, i, i, a, x[i], b, y[i], z[i]);
    }
    else
    {
        printf(" * \tTiempo: ((Reserva+inicialización) host %11.9f) + (target enter data %11.9f) + (target1 %11.9f) + (host actualiza %11.9f) + (target data update %11.9f) + (target2 %11.9f) + (target exit data %11.9f)= %11.9f\t / Tamaño Vectores:%d\t/ alpha*x[0]+beta*y[0]=z[0](%8.6f*%8.6f+%8.6f*%8.6f=%8.6f) / / alpha*x[%d]+beta*y[%d]=z[%d](%8.6f*%8.6f+%8.6f*%8.6f=%8.6f) /\n",
               t1 - t0, t2 - t1, t3 - t2, t4 - t3, t5 - t4, t6 - t5, t7 - t6, t7 - t0, N, a, x[0], b, y[0], z[0], N - 1, N - 1, N - 1, a, x[N - 1], b, y[N - 1], z[N - 1]);
    }

    free(x);
    free(y);
    free(z);

    return 0;
}
