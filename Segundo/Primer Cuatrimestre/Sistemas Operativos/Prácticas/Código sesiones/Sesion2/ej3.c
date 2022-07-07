#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

void buscar_dir(DIR *direct, char pathname[], int *reg, int *tamanio) {

	DIR *subdirect;
	char cadena[100];
	struct dirent *ed;
	struct stat atributos;
	
	while((ed = readdir(direct)) != 0){
		if(strcmp(ed->d_name != ".") && strcmp(ed->d_name != "..")){
			sprintf(cadena, %s/%s, pathname, ed->d_name);
			
			lstat(cadena,&atributos);
			
			if(S_ISDIR(atributos.st_mode)){
				subdirect = opendir(cadena);
				buscar_dir(subdirect,cadena,reg,tamanio);
			}
			
			else{
				if(IS_ISREG(atributos.st_mode) && ((atributos.st_mode && S_IXGRP) == S_IXGRP) && ((atributos.st_mode && S_IXOTH) == S_IXOTH))){
					printf(%s %ld \n; cadena; atributos.st_ino);
					(*reg)++;
					(*tamanio)+=(int)atributos.st_size;
				}
			}
	         }
        }
}

int main(int argc, char *argv[]){
	
		DIR *direct;
		int reg = 0;
		int tamanio = 0;
		
		direct = opendir(argv[1]);
		
		printf("Los nodos son: \n\n");
		buscar_dir(direct,argv[1],reg,tamanio);
		printf("Hay %d archivos regulares con permiso x para grupo y otros\n",reg);
		printf("El tamaño total que ocupan dichos archivos es de %d bytes\n",tamanio);
		
		return 0;
}
