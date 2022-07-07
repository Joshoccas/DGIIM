#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd1;
	int fd2;
	
	fd1 = open(argv[1],O_RDONLY,S_IRUSR);
	fd2 = open("salida",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
	int terminado = 1;
	
	for(int i = 1; terminado > 0 ;i++){
		
		char buf[80];
		if(read(fd1,buf,80) == 0){
			terminado = 0;
		}
		else{
			char cad_bloque[40];
			sprintf(cad_bloque, "\n%s%d\n", "Bloque",i);
			write(fd2,cad_bloque,strlen(cad_bloque));
			write(fd2,buf,80);
		}
	}
		
	return 0;
}
