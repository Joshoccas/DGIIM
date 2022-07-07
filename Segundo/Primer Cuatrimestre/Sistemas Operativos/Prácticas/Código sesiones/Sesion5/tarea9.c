// tarea9.c 

#include <stdio.h>
#include <signal.h>

int main()
{
struct sigaction sa;
sa.sa_handler = SIG_IGN; // ignora la señal
sigemptyset(&sa.sa_mask); 

//Reiniciar las funciones que hayan sido interrumpidas por un manejador 
sa.sa_flags = SA_RESTART; 

if (sigaction(SIGINT, &sa, NULL) == -1)
{ printf("error en el manejador");}
while(1);
}
