

// Ver que es un directorio

    struct stat atrdir;
   
    if (lstat (argv[], &atrdir) < 0) {
        printf ("\nError al intentar acceder a los atributos de %s\n\n", argv[]);
        perror("\nError en lstat\n\n");
        exit (EXIT_FAILURE);
    }

    if (!S_ISDIR(atrdir.st_mode)) {
        printf ("\nIntroduzca un directorio válido como primer argumento al ejecutable\n\n");
		exit (EXIT_FAILURE);
    }


// Ver que es entero positivo

    // -> al ppio #define DEC 10

    errno = 0; // para ver si ha habido error

    int num = strtol(argv[], NULL, DEC);

    if (errno || num < 0 || (num == 0 && !strcmp(argv[], "0"))) {
        perror("\nError: no es entero positivo\n\n");
        exit (EXIT_FAILURE);
    }