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
	pid_t buf[numhijos];
	
	for(int i = 0; i < numhijos; i++){
		if((pid = fork()) < 0){
			perror("Error en el fork");
			exit(-1);
		}
		
		buf[i] = pid;
		
		if(!pid)
			break;
	}
	
	if(pid == 0)
		printf("Soy el hijo %d\n",getpid());
	else{
		for(int i = 4; i >= 0; i-=2){
			pid = waitpid(buf[i], NULL, 0);
			numhijos--;
			printf("Acaba de finalizar mi hijo con PID %d\n",pid);
			printf("Solo me quedan %d hijos vivos\n",numhijos);
		}
		
		for(int i = 3; i > 0; i-=2){
			pid = waitpid(buf[i],NULL, 0);
			numhijos--;
			printf("Acaba de finalizar mi hijo con PID %d\n",pid);
			printf("Solo me quedan %d hijos vivos\n",numhijos);
		}
	}	
	
	return 0;
}
