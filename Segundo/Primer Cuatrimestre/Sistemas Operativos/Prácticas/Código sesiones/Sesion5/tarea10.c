// tarea10.c 

#include <stdio.h>
#include <signal.h>

static int s_recibida=0;
static void handler (int signum){
printf("\n Nueva accion del manejador \n");
s_recibida++;
}

int main()
{
struct sigaction sa;
sa.sa_handler = handler; // ignora la se–al
sigemptyset(&sa.sa_mask); 

//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
sa.sa_flags = SA_RESTART; 

if (sigaction(SIGINT, &sa, NULL) == -1)
{ 
printf("error en el manejador");}
while(s_recibida<3);
}