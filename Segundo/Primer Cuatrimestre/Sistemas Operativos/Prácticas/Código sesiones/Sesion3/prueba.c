#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	int *pid, i, aux;
	int numeroHijos = 5;
	int pid_org = getpid();
	char buf[256];

	// Control de parámetros
	if (argc != 1){
		perror("La función no debe recibir argumento\n");
		exit(-1);
	}

	pid = malloc(numeroHijos*sizeof(int));

	// Convertimos la salida en unbuffered
	setvbuf(stdout, buf, _IONBF, strlen(buf));
	// Ahora printf(buff) equivale a write(STDOUT_FILENO, buff, strlen(buff))
	// write imprime directamente en la terminal sin buffer. Pero como vimos en el ejercicio 2
	// printf si utiliza buffer, por lo que lo desactivamos para que se imprima
	// solo el del proceso que estamos ejecutando en ese moento

	for(i=0; i<numeroHijos && pid_org == getpid(); i++){
		pid[i] = 0;

		if((pid[i]=fork()) < 0){
			perror("Error en el fork\n");
			exit(-1);
		}
		else if(pid[i] == 0){	// Hijo
			printf("Soy el hijo %d\n", getpid());
			// sprintf(buff, "Soy el hijo %d\n", getpid());
			// write(STDOUT_FILENO, buff, strlen(buff));
		}
	}

	for(i=1; i<=numeroHijos && pid_org == getpid(); i++){
		aux = wait(0);	// Espera a que termine el hijo y devuelve su pid en ese instate

		/*	DESCRIPTION
		       All of these system calls are used to wait for state changes in a child
		       of the calling process, and obtain information about  the  child  whose
		       state  has changed.  A state change is considered to be: the child ter‐
		       minated; the child was stopped by a signal; or the child was resumed by
		       a  signal.  In the case of a terminated child, performing a wait allows
		       the system to release the resources associated with  the  child;  if  a
		       wait  is not performed, then the terminated child remains in a "zombie"
		       state (see NOTES below).
		       If a child has already changed state, then these calls  return  immedi‐
		       ately.   Otherwise,  they block until either a child changes state or a
		       signal handler interrupts the call (assuming that system calls are  not
		       automatically restarted using the SA_RESTART flag of sigaction(2)).  In
		       the remainder of this page, a child whose state has changed  and  which
		       has  not  yet  been  waited upon by one of these system calls is termed
		       waitable.
			
			The value of pid can be:
		       < -1   meaning  wait  for  any  child process whose process group ID is
		              equal to the absolute value of pid.
		       -1     meaning wait for any child process.
		       0      meaning wait for any child process whose  process  group  ID  is
		              equal  to that of the calling process at the time of the call to
		              waitpid().
		       > 0    meaning wait for the child whose process  ID  is  equal  to  the
		              value of pid.
		*/

		if(aux == -1){	// Significa que ha fallado
			perror("Error en el waitpid\n");
			exit(-1);
		}else{
			printf("Acaba de finalizar mi hijo %d\nMe quedan %d hijos vivos\n", aux, numeroHijos-i);
		}
	}

	free(pid);
	exit(EXIT_SUCCESS);
}
