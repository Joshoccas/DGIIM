// tarea11.c

#include <stdio.h>
#include <signal.h>

int main()

{
sigset_t new_mask;

/* inicializar la nueva mascara de señales */
sigemptyset(&new_mask);

sigaddset(&new_mask, SIGUSR1);

/*esperar a cualquier señal excepto SIGUSR1 */
sigsuspend(&new_mask);

}