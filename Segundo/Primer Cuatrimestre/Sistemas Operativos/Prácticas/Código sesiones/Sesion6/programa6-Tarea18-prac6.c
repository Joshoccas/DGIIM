#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
        
  int fd;
  char *p;
        
  fd = open("/dev/zero", O_RDONLY);
  
  p = (char *) mmap (0, sizeof(int), PROT_READ , MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
       printf("Fallo el mapeo\n");
       return 1;
  }
  close(fd);
  return EXIT_SUCCESS;
}
					  
