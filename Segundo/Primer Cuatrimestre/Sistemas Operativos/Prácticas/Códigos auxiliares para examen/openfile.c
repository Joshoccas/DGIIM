


// Apertura de un archivo

    int fd;

    if ((fd=open(argv[],O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))<0) {	// archivo lectura y escritura (lo creamos si no existe y borramos su contenido si ya existe)
        printf("\nError %d en open file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

// Lectura de un archivo

    int readable;
    char bufr[BYTES];

    readable = (read(fdr,bufr,BYTES)); // para ver si hemos leido 80B. read reposiciona el solito el puntero de lectura para la siguiente vuelta al bucle

    if (readable == -1) {
        printf("\nError %d en read file\n",errno);
        perror("\nError en read\n");
        exit(EXIT_FAILURE);
    }

// Escritura en un archivo

    if(write(fdw,bufr,BYTES) != BYTES) {	// escribe lo guardado en el búfer bufr en el archivo fdw
		perror("\nError en escritura \n");	
		exit(EXIT_FAILURE);
	}