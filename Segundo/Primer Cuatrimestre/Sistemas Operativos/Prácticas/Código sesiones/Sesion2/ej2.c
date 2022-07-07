#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{

	DIR *dir;
	struct dirent *ed;
	struct stat atributos;
	int permisosnuevos, permisosantiguos;
	permisosnuevos = strtol(argv[2], NULL, 8);
	dir = opendir(argv[1]);
	char pathname[500];
	
	while(ed = readdir(dir) != NULL){
		sprintf(pathname,%s/%s,argv[1],ed->d_name);
		lstat(pathname,&atributos);
		permisosantiguos = atributos.st_mode;
		if(chmod(pathname,permisosnuevos) < 0)
			printf("%s: %d %o", ed->d_name, errno, atributos.st_mode);
		else
			printf("%s: %o %o", ed->d_name, permisosantiguos, permisosnuevos);
	}
	
	close(dir);
	
	return 0;
}
