#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
char buf1[40];
char titulo[100];

int main(int argc, char *argv[])
{
int fdin;
int fdout;

if( (fdin=open(argv[1],O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

if( (fdout=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

for(int i = 0; read(fdin,buf1,80) > 0 ; i++){

	sprintf(titulo, "%s%d\n", "Bloque", i);
	write(fdout, titulo, strlen(titulo));
	write(fdout, buf1, strlen(buf1));
	lseek(fdin,80,SEEK_SET);
	lseek(fdout,80,SEEK_SET);
}

close(fdin);
close(fdout);


return EXIT_SUCCESS;
}
