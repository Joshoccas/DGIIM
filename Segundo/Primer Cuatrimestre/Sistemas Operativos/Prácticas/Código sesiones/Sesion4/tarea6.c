/*
tarea6.c
Trabajo con llamadas al sistema del Subsistema de Procesos y Cauces conforme a POSIX 2.10
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int fd[2], numBytes;
pid_t PID;
char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
char buffer[80];

pipe(fd); // Llamada al sistema para crear un cauce sin nombre

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if (PID == 0) {
	//Cierre del descriptor de lectura en el proceso hijo
	close(fd[0]);
	// Enviar el mensaje a traves del cauce usando el descriptor de escritura
	write(fd[1],mensaje,strlen(mensaje)+1);
	exit(EXIT_SUCCESS);
}
else { // Estoy en el proceso padre porque PID != 0
	//Cerrar el descriptor de escritura en el proceso padre
	close(fd[1]);
	//Leer datos desde el cauce.
	numBytes= read(fd[0],buffer,sizeof(buffer));
	printf("\nEl numero de bytes recibidos es: %d",numBytes);
	printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
}

return EXIT_SUCCESS;
}

