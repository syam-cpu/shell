#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "inbuilt.h"
#include "prompt_n_parse.h"
int inbuilt(){
	extern char *part[1000];
	extern char *str;
	extern char *pref;
	char pwd[6]="pwd\n";
	char echo[6]="echo";
	char cd[6]="cd";
	extern int nop;
	int r = 0;

	if(strcmp(pwd,part[0])==0 || strcmp("pwd",part[0])==0){
		
		char *buffer = (char *) malloc(10000 * sizeof(char));
		getcwd(buffer,1024);
		printf("%s\n",buffer);r=1;
		
	}
	else if(strcmp(echo,part[0])==0){
		for(int i = 1;i<nop-1;i++)printf("%s ",part[i]);
		printf("%s\n",part[nop-1]);
		r=1;

		
	}
	else if(strcmp("echo\n",part[0])==0){
		printf("\n");
		r=1;


	}
	if(strcmp(part[0],"cd")==0){
          if(strcmp("cd",part[0])==0 && nop==1){chdir(pref);
		 free(str);
                        str=(char*)malloc(100000 * sizeof(char));
                        str[0]='\0';
			r=1;

	}
	else if(strcmp(part[1],"\0") ==0){
		chdir(pref);
                 free(str);
                        str=(char*)malloc(100000 * sizeof(char));
                        str[0]='\0';
                        r=1;
	}




	else{

	char *val;
	 char * vales = (char *) malloc(10000 * sizeof(char));
           if(nop>=2){
	 strcpy(vales,part[1]);
         val = strsep(&vales,"\n");
	   }


	 if(strcmp(cd,part[0])==0){
		  char *cwd = (char *) malloc(10000 * sizeof(char));
                getcwd(cwd,1024);
                int l1=strlen(pref);
                int l2=strlen(cwd);

		 if(strcmp(val,"..")==0){
			 r=1;
			 chdir(val);
	        char *cwd1 = (char *) malloc(10000 * sizeof(char));
                getcwd(cwd1,1024);
		int l3=strlen(cwd1);
		free(str);
                str=(char*)malloc(10000 * sizeof(char));

		if(l3<l1){
			strcpy(str,cwd1);
		}
		else if(l3==l1){
			str[0] = '\0';
		}

		else{
			for(int i=l1;i<l2;i++)str[i-l1]=cwd1[i];

		}
		 }
	       else if(strcmp(val,".")==0){
		        r=1;
			 char *cwd1 = (char *) malloc(10000 * sizeof(char));
                getcwd(cwd1,1024);

			if(l2<=l1)chdir(cwd1);
		}
		else if(strcmp(val,"~")==0){
			r=1;
			chdir(pref);
			free(str);
			str=(char*)malloc(100000 * sizeof(char));
			str[0]='\0';
		}
		else{
			r=1;

			int l = chdir(val);

		if(l==0){
		char *cwd1 = (char *) malloc(10000 * sizeof(char));
                getcwd(cwd1,1024);
                int l3=strlen(cwd1);
		int l1= strlen(pref);
		int l2 = strlen(val);

		int len = strlen(pref);
		int ok = 1;
		for(int i=0;i<len && i<l3 ;i++){
			if(pref[i]!=cwd1[i]){
				ok=0;
			
			}
		}

		if(ok ==0 || l3<len){
		
			free(str);
			   str = (char *) malloc(10000* sizeof(char));

			strcpy(str,cwd1);
		}
		else if(l3==len){
			free(str);
                           str = (char *) malloc(10000* sizeof(char));
			   str[0]='\0';
		}



		
		else{

			char v[100]="/";

			strcat(v,val);
			strcat(str,v);
		}
	        

	
		
		}
		else{
			perror("ffffff");
		}
	}}}}
	else{
		
	}

	


		


	if(r==1)
	return 1;
	else
	return 0;
}


