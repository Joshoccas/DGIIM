#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
        struct stat sb;
        off_t len;
        char *p;
        int fd;

        if (argc != 3) {
                printf("Uso: %s archivo numero\n", argv[0]);
                return EXIT_FAILURE;
        }

        fd = open (argv[1], O_RDONLY);
        if (fd == -1) {
                printf("Error al abrir archivo\n");
                return EXIT_FAILURE;
        }

        if (fstat (fd, &sb) == -1) {
                printf("Error al hacer stat\n");
                return EXIT_FAILURE;
        }

        if (!S_ISREG (sb.st_mode)) {
                printf ("%s : no es un archivo regular\n", argv[1]);
                return EXIT_FAILURE;
        }

        p = (char *)mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED) {
                printf("Fallo el mapeo\n");
                return EXIT_FAILURE;
        }

        if (close (fd) == -1) {
                printf("Error al cerrar el archivo\n");
                return EXIT_FAILURE;
        }
	/* mostramos el archivo completo */
        printf ("%s\n", p);
	/* Mostramos en byte con desplazamiento argv[2] */
	printf ("Byte con desplazamiento %s es %d: \n", argv[2], p[atoi(argv[2])]);
	
        if (munmap (p, sb.st_size) == -1) {
                printf("Error al cerrar la proyeccion \n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
					  
