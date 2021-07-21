#include "pinfomodule.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include "prompt_n_parse.h"
void pinfomodule(char *f,char y){
	int x =chdir(f);
	extern char *pref;
	if(x!=0){
	perror("no such process with that id");
	return;
	}
	extern int nop;

	char *copy;
	copy = (char *) malloc(10000 * sizeof(char));
	strcat(copy,f);


	strcat(f,"/stat");
	

   char *filecon = (char *) malloc(10000 * sizeof(char));
   int fd1 = open (f, O_RDONLY);
   read (fd1, filecon, 10000);

     parse(filecon);
     extern char *part[1000];

	           printf("pid -- ");		   
                   printf("%s\n", part[0]);
		   printf("Process status -- ");
		   printf("%s\n", part[2]);
		   printf("memory -- ");
		   printf("%s\n", part[22]);

	           strcat(copy,"/exe");
		   
	  
		   char * buf;
		   buf =  (char *) malloc(10000 * sizeof(char));
		    int l =readlink(copy,buf,1024);
		    if(l!=-1){
		    printf("Executable Path -- ");
		   printf(" %s\n",buf);
		    }
	   
	   else{
		    printf("Executable Path -- ");
		    printf("%s\n",part[1]);
	   }

	   chdir(pref);
	    


    

}
