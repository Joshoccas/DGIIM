/**
 * 
 * Directiva parallel
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif
/**
 * @file  parallel.c
 * @brief _El mensaje a imprimir depende del número de hilo que se introduce como parámentro ####_
 *  @author Extraído del libro: Chapman, B: Using OpenMP. Portable Shared Memory Parallel Programming
 *  DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 *  @copyright 2009 Sun Microsystems, Inc. All rights reserved.
 *
 *   The contents of this file are subject to the terms of the BSD License("BSD")(the "License").
 *   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt
 *
 *  The BSD License
 *
 *  Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *
 *      * Redistribution of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 *      * Redistribution in binary form must reproduce the above copyright
 *         notice, this list of conditions and the following disclaimer in
 *         the documentation and/or other materials provided with the
 *         distribution.
 *       * Neither the name of Sun Microsystems, Inc. or the names of
 *         contributors may be used to endorse or promote products derived
 *         from this software without specific prior written permission.
 *
 *   This software is provided "AS IS," without a warranty of any kind. ALL
 *   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
 *   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 *   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND
 *   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A
 *   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 *   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT
 *   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR
 *   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY,
 *   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS
 *   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *   You acknowledge that this software is not designed, licensed or intended for
 *   use in the design, construction, operation or maintenance of any nuclear facility.
 *
 * @param Hebra=atoi(argv[1]) número de hilo
 * @return 0 upon exit success (print mensaje y número de hilo que lo imprime)
 *
 * **Objetivo**
 *
 * El código ilustra:
 *
 * - Directivas <tt>parallel</tt>
 *
 * - Funciones <tt>omp_get_thread_num(), devuelve el identificador del hilo que lo ejecuta </tt>
 *
 * **Compilación**
 * @code
 * gcc -O2 -fopenmp -o parallel parallel.c
 * @endcode
 *
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * parallel 2    (número de hilo)
 * ~~~~~~~~~~~~~~~~~~~~~
 *
 */
int main(int argc, char **argv)
{
   int Hebra;

   if(argc < 2)     {
    fprintf(stderr,"\n[ERROR] -: Hay un parámetros de entrada: número de hebra \n");
          exit(-1);
     }
   Hebra = atoi(argv[1]);

#pragma omp parallel 
   {
     if ( omp_get_thread_num() < Hebra ) 
        printf("  Hebra %d realiza la tarea 1\n",
               omp_get_thread_num());
     else 
	printf("  Hebra %d realiza la tarea 2\n",
               omp_get_thread_num());
   }

   return(0);
}
