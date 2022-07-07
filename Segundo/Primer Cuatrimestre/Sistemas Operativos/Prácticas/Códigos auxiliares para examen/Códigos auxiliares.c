
#include <stdlib.h>     // Siempre
#include <unistd.h>     // Siempre
#include <stdio.h>      // (s)printf | setvbuf
#include <sys/types.h>  // lseek | opDirectorios | wait | fork | mknod/mkfifo | kill | (f)truncate
#include <sys/stat.h>   // (l/f)stat | mknod/mkfifo
#include <sys/wait.h>   // wait
#include <dirent.h>     // opDirectorios
#include <ftw.h>        // nftw
#include <string.h>     // strlen | strcpy | strcat | strcmp ...
#include <fcntl.h>      // mknod/mkfifo | fcntl
#include <signal.h>     // kill | sigaction | sigprocmask
#include <sys/file.h>   // flock
#include <sys/mman.h>   // mun/mmap


void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/*
// Máscara de bits para comprobar si es un archivo regular
#define S_ISREG2(mode)  ((mode & S_IFMT) == S_IFREG)

*/

int main(int argc, char *argv[])
{
/*
    // Comprobar parámetros
    if (argc != x){
        printf("\nUso: ./prueba <>");
        error("\nError en argumentos")
    }

    // Abrir un archivo para salida
    if ((fd_out=open(path_out,O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU)) < 0) {
		error("\nError en open\n");
 	}

    // Abrir archivo para entrada
    if ((fd_in=open(path_out,O_RDONLY,S_IRWXU)) < 0) {
		error("\nError en open\n");
 	}
    
    // Escribir en una cadena de caracteres
    sprintf(linea, msg, variables...);

    // Moverse dentro de un fichero
    lseek(fd, off_set, whence[SEEK_sth]);

    // Desactivar los permisos activados por open
    umask(0):

    // Cambiar permisos
    if (f/chmod(fd/path, permisos[S_ISsth]) < )
        error("\nError en f/chmod");

    // Trabajar con directorios
    if ((<DIR *> dir = opendir(path)) == NULL) 
		error ("\nError en opendir");
    while ((<struct dirent *> archivo = readdir(dir)) != NULL) {}

    // Mascara de flags de un archivo
    if(f/stat(fd/pathname,<struct stat> &atributos) < 0)
		error("\nError en stat");
    
    // Recorrer un directorio recursivamente
    if (nftw(dirPath,<int> func(archPath, atributos, flags, ftw), 10, 0) < 0)
        error("\nError en nftw");
    
    // Identificadores
    <pid_t> getpid();
    <pid_t> getppid();
    <uid_t> getuid();
    <uid_t> geteuid();
    <gid_t> getgid();
    <gid_t> getegid();

    // Crear un proceso hijo y usarlo
    if ((pid = fork()) < 0){
        error ("Error en fork\n");
    } else if (!pid) {
        printf("\nHola, soy el proceso hijo\n");
    } else 
        <ejecuciones padre>
    // vfork() es igual pero no copia el espacio de direcciones

    // Esperar al hijo
    <pid_t> wait(0);
    <pid_t> waitpid(pid[i], NULL, NULL);

    // Desabilitar el buffering de la salida estandar
    if(setvbuf(stdout,NULL,_IONBF,0)) 
	    error("\nError en setvbuf");
    
    // Ejecutar otros programas dentro de un progama
    if (execvp(args[0], args) < 0) 
        error ("Error en execvp");
    // execlp(nombre, nombre, arg1,..., NULL)
    
    // Crear el vector de argumentos
    for (int i=1; i<=n_args; ++i) {
		args[i-1] = (char*) malloc(strlen(argv[i])+1);
		strcpy(args[i-1], argv[i]);
	}
	args [n_args+1] = NULL;

    // Cauces con nombre 
    mknod(ARCHIVO_FIFO,S_IFIFO|0666,0); //también vale: mkfifo(ARCHIVO_FIFO,0666);
    if ( (fd1=open(ARCHIVO_FIFO,O_RDWR)) <0) 
        error("Error en open");
    <int> read(fd1,<char*> buffer, size);
    if( (fd2=open(ARCHIVO_FIFO,O_WRONLY)) <0) 
        error("\nError en open");
    if( (write(fd2, buffer, strlen(buffer)+1)) != strlen(buffer)+1) {
        error("\nError al escribir en el FIFO");
    
    // Cauces sin nombre
    pipe (fd[2]);
    dup2 (fd[0], STDIN_FILENO);
    dup2 (fd[1], STDOUT_FILENO);

    // Comunicación
    read(fd, <char *>buf, nbytes);
    <size_t> write (fd, <void *>buf, nbytes);

    // Trabajar con señales
    kill(fd, señal);
    sigaction(signum, <const struct sigaction *> act, <struct sigactioin*> oldact);

    // Inicializar struct sigaction sig_act;
    sig_act.sa_handler= func_handler<(<int> signum)>;
	sigemptyset / sigfillset (&sig_act.sa_mask); // Ver más
	sig_act.sa_flags = 0;

    // Examiar cambiar máscaras de señales
    if (sigprocmask(modo, &new_mask, &old_mask) < 0)    // Si new_+mask = NULL -> consultiva
        error ("\nError en sigprocmask");               // old_mask puede ser NULL

    // Obtener o modificar banderas
    if (fcntl(fd, F_GETFL) == -1)     
        error("Error en fcntl\n");
    If (fcntl(fd, F_SETFL, bandera) == -1)     
        error("Error en fcntl\n");
    

    // Salida hacia un archivo (o cauce)
    close(STDOUT_FILENO);
    if (fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1)     
        error("Error en fcntl\n");

    // Entrada desde un archivo (o cauce)
    close(STDIN_FILENO);
    if (fcntl(fd, F_DUPFD, STDIN_FILENO) == -1)     
        error("Error en fcntl");


    // Bloquear un archivo completo
    flock(fd, operation);

    // Bloquear una región de un archivo
    struct flock cerrojo;
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;
    if (fcntl(fd, F_SETLK(W), &cerrojo) == -1)
        error("\nError en cerrojo");
    
    // Asignar longitud a un archivo
    if (ftruncate(fd, size) < 0)
        error("\nError en ftruncate");
    
    // Crear proyecciones
    if ((ptr = mmap(NULL, size, PROT_READ/WRITE, MAP_PRIVATE/SHARED, fd1, SEEK_SET/END)) == MAP_FAILED)
        error("\nError en mmap");
    
    // Cerrar proyecciones
    if (munmap(ptr, size) < 0 )
        error("\nError en munmap");

*/
    return 0;
}
