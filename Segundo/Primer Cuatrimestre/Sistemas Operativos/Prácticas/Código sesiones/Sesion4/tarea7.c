/*
tarea7.c
Programa ilustrativo del uso de pipes y la redirecci�n de entrada y
salida est�ndar: "ls | sort"
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]) 
{
int fd[2];
pid_t PID;

pipe(fd); // Llamada al sistema para crear un pipe

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if(PID == 0) { // ls
	//Establecer la direccion del flujo de datos en el cauce cerrando
	// el descriptor de lectura de cauce en el proceso hijo
	close(fd[0]);

	//Redirigir la salida estandar para enviar datos al cauce
	//--------------------------------------------------------
	//Cerrar la salida estandar del proceso hijo
	close(STDOUT_FILENO);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estandar (stdout)
	dup(fd[1]);
	execlp("ls","ls",NULL);
}
else { // sort. Estoy en el proceso padre porque PID != 0

	//Establecer la direcci�n del flujo de datos en el cauce cerrando
	// el descriptor de escritura en el cauce del proceso padre.
	close(fd[1]);

	//Redirigir la entrada est�ndar para tomar los datos del cauce.
	//Cerrar la entrada est�ndar del proceso padre
	close	(STDIN_FILENO);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada est�ndar (stdin)
	dup(fd[0]);
	execlp("sort","sort",NULL);
}

return EXIT_SUCCESS;
}


