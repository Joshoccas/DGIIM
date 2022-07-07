//ejercicio3.1.c

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2){
		perror("Solo se debe introducir un entero como argumento");
		exit(EXIT_FAILURE);
	}
	
	else{
		int entero = atoi(argv[1]);
		pid_t id_padre;
		
		if((id_padre = fork())<0){
			perror("Error en el fork");
			exit(EXIT_FAILURE);
		}
		
		else{
			if(id_padre == 0){
				if(entero % 4 == 0)
					printf("El número %d es divisible por 4\n",entero);
				else
					printf("El número %d no es divisible por 4\n",entero);
			}
			
			else{
				if(entero % 2 == 0)
					printf("El número %d es par\n",entero);
				else
					printf("El número %d no es par\n",entero);
			}
		}
	}
	
	exit(EXIT_SUCCESS);
}
