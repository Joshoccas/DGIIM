#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
	int numhijos = 5;
	pid_t pid;
	int estado;
	
	for(int i = 0; i < numhijos; i++){
		if((pid = fork()) < 0){
			perror("Error en el fork");
			exit(-1);
		}
		
		if(!pid)
			break;
	}
	
	if(pid == 0)
		printf("Soy el hijo %d\n",getpid());
	else{
		for(int i = numhijos; i > 0; i--){
			pid = wait(&estado);
			printf("Acaba de finalizar mi hijo con PID %d\n",pid);
			printf("Solo me quedan %d hijos vivos\n",i);
		}
	}	
	
	return 0;
}
