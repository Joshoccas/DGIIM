#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int MMAPSIZE=1024;

int main()
{
 
  int fd, num, i;
  char ch='\0';
  char *memoria;
  umask(0);
  fd = open("Archivo", O_RDWR|O_CREAT|O_EXCL, S_IRWXU);
  if (fd == -1) {
    perror("El archivo existe");
    exit(1);
  }
 for (i=0; i < MMAPSIZE; i++){
      num=write(fd, &ch, sizeof(char));
      if (num!=1) printf("Error escritura\n");
  }
  memoria = (char *)mmap(0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (memoria == MAP_FAILED) {
      perror("Fallo la proyeccion");
      exit(2);
  }
 
  close(fd);  /* ya no es necesario el descriptor*/
  strcpy(memoria, "hola mundo\n");  /* copia la cadena en la proyeccion */
  exit(0);
}
