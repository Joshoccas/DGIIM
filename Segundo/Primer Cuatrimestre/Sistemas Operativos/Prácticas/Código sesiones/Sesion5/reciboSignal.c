/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilizaci—n de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepci—n de una se–al.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum)
  {

    if(sigNum == SIGUSR1)
    printf("\nRecibida la senal SIGUSR1\n\n");
    else if(sigNum == SIGUSR2)
    printf("\nRecibida la senal SIGUSR2\n\n"); 
   }

int main(int argc, char *argv[])
   {
    struct sigaction sig_USR_nact;
    if(setvbuf(stdout,NULL,_IONBF,0)) 
       {    perror("\nError en setvbuf");
       }

//Inicializar la estructura sig_USR_na para especificar la nueva acci—n para la se–al.

sig_USR_nact.sa_handler= sig_USR_hdlr;


//'sigemptyset' inicia el conjunto de se–ales dado al conjunto vacio. 

sigemptyset (&sig_USR_nact.sa_mask);
sig_USR_nact.sa_flags = 0;

//Establecer mi manejador particular de se–al para SIGUSR1
if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0) 
    {
	perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
	exit(EXIT_FAILURE);
    }
//Establecer mi manejador particular de se–al para SIGUSR2
if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) 
    {
	perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
	exit(EXIT_FAILURE);
    }
for(;;)
   {
   }
}