


// Abrimos el directorio

    DIR * directorio;
    if ((directorio = opendir (dir)) == NULL) {
        printf ("\nError al intentar abrir el directorio %s\n\n", dir);
        perror("\nError en opendir\n\n");
        exit (EXIT_FAILURE);
    }

// Recorremos el directorio

    struct dirent * file;       // archivo leído
    struct stat metadatafile;   // para los metadatos del archivo leído en cada vuelta del bucle

    errno = 0; // para ver si ha habido error al recorrer el directorio

    while ((file = readdir (directorio))!= NULL) {
        
        // Arriba hemos leído el archivo que toque y comprobado que no es NULL

        // Necesitamos la ruta al file en formato directorio/file
        char path[TAM];
        sprintf(path,"%s/%s",dir,file->d_name);

        // Conseguimos los metadatos de file
        if (stat (path, &metadatafile) < 0) {
            printf ("\nError al intentar acceder a los atributos de %s\n\n", path);
            perror("\nError en stat\n\n");
            exit (EXIT_FAILURE);
        }
        
    }

    // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
    // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

    if (errno) { // si es distinto de 0
        printf ("\nError al recorrer el directorio %s con error %d\n\n", dir, errno);
        perror("\nError en readdir\n\n");
        exit (EXIT_FAILURE);
    }