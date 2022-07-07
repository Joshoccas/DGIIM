#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{

pid_t id_padre;
int numerohijos = 5;
int estado;

for(int i = 0; i < numerohijos; i++){
	id_padre = fork();
	if(id_padre == 0)
		printf("Soy el hijo %d\n",getpid());
}


for(int i = 0; i < numerohijos; i++){
	id_padre = wait(&estado);
	numerohijos--;		
	printf("Acaba de finalizar mi hijo %d\n",id_padre);
	printf("Solo me quedan %d hijos vivos\n",numerohijos);
	
}
return 0;
}
