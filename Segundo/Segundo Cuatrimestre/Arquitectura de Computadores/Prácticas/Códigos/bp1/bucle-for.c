/**
 * 
 Directiva bucle-for
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
 * @file  bucle-for.c 
 * @brief _Muestra que se reparten las iteraciones del bucle entre los hilos de forma que cada iteración se ejecuta una vez_
 * @author Extraído del libro: Chapman, B: Using OpenMP. Portable Shared Memory Parallel Programming
 * 
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
 * @param n=atoi(argv[1])  número de iteraciones del bucle
 * @return 0 upon exit success (print iteración y hilo que la ejecuta)
 *  
 * **Objetivo**
 * 
 * El código ilustra:
 * 
 * - Directivas <tt> for, parallel</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o bucle-for bucle-for.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * bucle-for 
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
   int i, n = 9;

  if(argc < 2)     {
    fprintf(stderr,"\n[ERROR] - Falta nº de iteraciones \n");
          exit(-1);
     }
   n = atoi(argv[1]);
#pragma omp parallel for
{
   for (i=0; i<n; i++)
      printf("Hebra %d ejecuta la iteración %d del bucle\n",
             omp_get_thread_num(),i);
}

   return(0);
}
