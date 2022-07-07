#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
        
  char *p;
        
  p = (char *) mmap (0, sizeof(char), PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
  if (p == MAP_FAILED) {
       printf("Fallo el mapeo\n");
       return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
					  
