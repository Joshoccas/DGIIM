#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int primo(int num){
	int resultado = 1;
	int tope = sqrt(num);
	for(int i = 2; (i<=num) && resultado; i++)
		if(num%i == 0)  resultado = 0;
	
	return resultado;
}

int main(int argc, char *argv[])
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	for(int i = a; i <= b; i++){
		if(primo(i)) write(STDOUT_FILENO,&i,sizeof(int));
	}
	
	return EXIT_SUCCESS;
}
