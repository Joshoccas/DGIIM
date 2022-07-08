/**
 * 
 * Cálculo de media aritmética, desviación media y desviación típica usando valores float
 * 
 */

#include <stdlib.h> // biblioteca con funciones atoi(), rand(), srand(), malloc() y free()
#include <stdio.h>  // biblioteca donde se encuentra la función printf()
#include <time.h>   // biblioteca donde se encuentra la función clock_gettime()
#include <math.h>   // sqrt()

#define NUM_SM 48 
#define NUM_UF 3072
#define NUM_UF_PER_SM NUM_UF/NUM_SM
#define MAX_NTHREADS_PER_SM 1024
#define MAX_NTHREADS_DEVICE MAX_NTHREADS_PER_SM*NUM_SM  
/**
 * @struct s_datos
 * @brief Estructura con registros de dos celdas, cada registro contiene un posible valor y su frecuencia
 */
struct s_datos {
       float x;             ///<valores float
       unsigned int f;      ///<frecuencias valores
};
/**
 * @file  dist_esta.c 
 * @brief #### media aritmética, desviación media y desviación típica usando valores float ####
 *  N=suma(fi)       suma de todas las frecuencias
 *  xmedia = suma(xi*fi)/N
 *  Dm=suma(abs(xi-xmedia)*fi)/N
 *  S=sqrt(suma((xi^2*fi)/N-xmedia^2)
 * 
 * @author Mancia Anguita López
 * 
 * @param Nv=atoi(argv[1])  número de valores distintos de la distribución estadística o de probabilidad (valores posibles + la frecuencia de que ocurran)
 * 
 * **Compilación en atcgrid4:**
 * @code
 * sbatch -Aaapt -paapt -watcgrid4 --wrap "nvc -O2 -lm -openmp -mp=gpu dist_esta.c  -o dist_esta"
 * @endcode
 * 
 *  **Ejecución en atcgrid4:**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun -Aaapt -paapt -watcgrid4 dist_esta  49152  //N=49152 es la longitud de la estructura de datos
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  int i;
  static float desvtip;
  static unsigned int Nf=0;
  static float cuadrados_x=0.0; static float mediaarit=0.0; static float dm=0.0;
  struct timespec cgt1, cgt2;
  double ncgt1; //para tiempo de ejecución

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc < 2)
  {
    printf("Faltan argumentos de entrada (n. valores)");
    exit(-1);
  }

  int Nv = atoi(argv[1]); // Máximo Nv =2^32-1=4294967295 (sizeof(int) = 4 B)
  

  struct s_datos *datos;
  datos=malloc(Nv * (sizeof(struct s_datos)));
 
  //Inicializar datos
  if (Nv < 9)
    for (i = 0; i < Nv; i++)
    {
      datos[i].x = Nv * 0.1 + i * 0.1;
      datos[i].f = i; //printf("%f=%f, %d=%d. \t", datos[i].x, N * 0.1 + i * 0.1, datos[i].f,i);
    }
  else
  {
    //srand(time(0));     //descomentar para que en cada ejecución la semilla sea distinta, si se usan hilos del SO sustituir por 
    for (i = 0; i < Nv; i++)
    {  //en lugar de rand y srand usar lrand48_r y srand48() cuando se usen hilos del SO (rand() no es reentrante y rand_r() se va a eliminar), usar drand48() para generar double
      datos[i].x = ((float) rand() / ((float)RAND_MAX)) * 10; //genera un número aleatorio de tipo float entre 0 y 10
      datos[i].f = datos[i].f = (rand()%100); //genera un número entero aleatorio entre 0 y 100 //((rand()+10) / (rand()))+1;  
    }
  }

  clock_gettime(CLOCK_REALTIME, &cgt1);
  //Cálculos  
  for (i = 0; i < Nv; i++) {
      Nf = Nf + datos[i].f;
      float xf=datos[i].x*(float)datos[i].f;
      mediaarit = mediaarit + xf;
      cuadrados_x = cuadrados_x + datos[i].x*xf; 
  }
    mediaarit = mediaarit/Nf;
    for (i = 0; i < Nv; i++) {
      float x = fabsf(datos[i].x-mediaarit); 
      dm = dm + x*datos[i].f; 
  }
    desvtip=sqrt(cuadrados_x/Nf - mediaarit*mediaarit);
    dm = dm / Nf;
  clock_gettime(CLOCK_REALTIME, &cgt2);
  ncgt1 = (double)(cgt2.tv_sec - cgt1.tv_sec) +
         (double)((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));

  //Imprimir resultado y el tiempo de ejecución
  if (Nv<11) {
    printf("Tiempo:%11.9f\t / Tamaño struct:%d\t / media aritmética:%11.6f\t desviación media:%11.6f \t desviación típica struct:%11.6f", ncgt1, Nv, mediaarit, dm, desvtip);
    printf("\ni\t\txi\t\tfi\n");
    for(i=0; i<Nv; i++)  printf("%d\t%11.6f\t\t%u\n",i,datos[i].x,datos[i].f); 
  }
else printf("Tiempo:%11.9f\t / Tamaño struct:%d\t / media aritmética:%11.6f\t desviación media:%11.6f \t desviación típica struct:%11.6f\n", ncgt1, Nv, mediaarit, dm, desvtip);

  
  free(datos); // libera el espacio reservado 

  return 0;
}