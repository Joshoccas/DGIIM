#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main(int argc, char *argv[]) {
    int fd[2];
    pid_t buf[2];
    pid_t PID;

    pipe(fd);

    if (argc != 2) {
        perror("Solo se aceptan como argumentos dos enteros (extremos intervalo)");
        exit(-1);
    }
    else{
            int inf = atoi(argv[2]);
            int sup = atoi(argv[3]);
            int sup1 = inf + (inf + sup) / 2;
            int inf2 = sup1 + 1;
            char buf1[] = argv[2];
            char buf2[] = itoa(sup1);
            char buf3[] = itoa(inf2);
            char buf4[] = argv[3];

            for (int i = 0; i < 2 && PID != 0; i++) {
                if (PID = fork() < 0) {
                    perror("Error en el fork");
                    exit(-1);
                }

                buf[i] = PID;
            }

            if (PID == buf[0]) {
                char aux1[100];
                char aux2[100];
                dup2(fd[0], STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
                read(fd[0], aux1, sizeof(buf1));
                read(fd[0], aux2, sizeof(buf2));
                execlp("programa1", "programa1", aux1, aux2, NULL);
            } else if (PID == buf[1]) {
                char aux3[100];
                char aux4[100];
                dup2(fd[0], STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
                read(fd[0], aux3, sizeof(buf3));
                read(fd[0], aux4, sizeof(buf4));
                dup2(fd[0], STDIN_FILENO);
                execlp("programa2", "programa2", aux3, aux4, NULL);
            } else {
                write(fd[1], buf1, sizeof(buf1));
                write(fd[1], buf2, sizeof(buf2));
                dup2(fd[0], STDIN_FILENO);
                waitpid(buf[0], NULL, 0);
                waitpid(buf[1], NULL, 0);
                char resultado[300];
                read(fd[0], resultado, 300);
                printf(resultado);
            }
    }

    return 0;
}
