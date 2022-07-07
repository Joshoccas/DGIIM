#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define _XOPEN_SOURCE 500
#include <ftw.h>


int reg;
int tamanio;

int trabajar(const char* path, const struct stat* stat, int flags, struct FTW*
ftw) {
	
	for(int i=0; i < ftw->level; i++)
		printf("\t");
	
	if(flags == FTW_D)
		printf("El directorio %s con inodo %ld contiene:\n", path, stat->st_ino);
	else if(flags == FTW_F)
		printf("Archivo: %s \t %ld", path, stat->st_ino);
	
	if(((stat->st_mode && S_IXOTH) == S_IXOTH) && ((stat->st_mode && S_IXGRP) == S_IXGRP)){
		reg++;
		tamanio+=stat->st_size;
	}
	
	return 0;
}

int main(int argc, char** argv) {

	
	if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
		perror("nftw");
	}
	
	printf("Existen %ld archivos regulares con permiso de ejecución para grupos y otros",reg);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes",tamanio);
	return 0;
}
