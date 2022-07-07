// gcc -Og bomba.c -o bomba -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 20

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"Â·Â·Â· bomba desactivada Â·Â·Â·\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"\n");
	exit(0);
}

int main(){
	char pw[SIZE];
	int  pc, n;
	char password[]="uncincosonseiscreditos\n";	// contraseÃ±a
	char fpassword[]="Jamaldosaluda\n";
	int  pin  = 1406;			// pin
	int  fpin = 1912;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseÃ±a: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	
	if(strncmp(pw,fpassword,sizeof(fpassword)))
	   printf("\nHas caído en mi trampa");
	    
	if(strncmp(pw,password,sizeof(password)))
		boom();

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );
	if    (pc != fpin){
	     printf("\nEsfuérzate más");
	}
	
	if    (	pc != pin )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
