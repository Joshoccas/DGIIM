/*
 envioSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada kill para enviar una señal:
 0: SIGTERM
 1: SIGUSR1
 2: SIGUSR2
  a un proceso cuyo identificador de proceso es PID.
 SINTAXIS: envioSignal [012] <PID> 
*/


#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types 
#include<limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
int main(int argc, char *argv[])
 {
          long int pid;
          int signal;
          if(argc<3) {
          printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n\n");
          exit(EXIT_FAILURE);
           }
         pid= strtol(argv[2],NULL,10);
         if(pid == LONG_MIN || pid == LONG_MAX) 
           {
         if(pid == LONG_MIN)
         printf("\nError por desbordamiento inferior LONG_MIN %ld",pid);
         else
            printf("\nError por desbordamiento superior LONG_MAX %ld",pid);
            perror("\nError en strtol");
            exit(EXIT_FAILURE);
           }
        signal=atoi(argv[1]);
        switch(signal) {
            case 0: //SIGTERM
            kill(pid,SIGTERM); break;
            case 1: //SIGUSR1
            kill(pid,SIGUSR1); break;
            case 2: //SIGUSR2
            kill(pid,SIGUSR2); break;
            default : // not in [012]
            printf("\n No puedo enviar ese tipo de senal"); 
              }
}