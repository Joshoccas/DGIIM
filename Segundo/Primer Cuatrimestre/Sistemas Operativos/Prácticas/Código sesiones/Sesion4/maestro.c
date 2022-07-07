#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int main(int argc, char *argv[])
{
	
	int inf1 = atoi(argv[1]);
	int sup2 = atoi(argv[2]);
	int sup1 = inf1 + (sup2-inf1)/2;
	int inf2 = sup2 + 1;
	char buf1[10];
	char buf2[10];
	
	int fd1[2];
	pid_t PID1;
	pipe(fd1);
	
	int fd2[2];
	pid_t PID2;
	pipe(fd2);
	
	if((PID1 = fork()) < 0){
		perror("Error en el fork\n");
		exit(-1);
	}
	else{
		if(PID1 == 0){
			close(fd1[0]);
			dup2(fd1[1],STDOUT_FILENO);
			sprintf(buf1,"%d",inf1);
			sprintf(buf2,"%d",sup1);
			execl("./esclavo","esclavo",buf1,buf2,NULL);
		}
		else{
			close(fd1[1]);
			int primo;
			while(read(fd1[0],&primo,sizeof(int))>0){
				printf("%d\n",primo);
			}
			close(fd1[0]);
		}
	}
	
	if((PID2 = fork()) < 0){
		perror("Error en el fork");
		exit(-1);
	}
	else{
		if(PID2 == 0){
			close(fd2[0]);
			dup2(fd2[1],STDOUT_FILENO);
			sprintf(buf1,"%d",inf2);
			sprintf(buf2,"%d",sup2);
			execl("./esclavo","esclavo",buf1,buf2,NULL);
		}
		else{
			close(fd2[1]);
			int primo;
			while(read(fd2[0],&primo,sizeof(int))>0){
				printf("%d\n",primo);
			}
			close(fd2[0]);
		}
	}
	
	
	return EXIT_SUCCESS;
}
