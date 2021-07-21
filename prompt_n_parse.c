#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "prompt_n_parse.h"
 
void prompt(char t[10000]){
	char *stre;
	stre = (char *) malloc(10000 * sizeof(char));
	stre[0]='\0';

	strcat(stre,"<");
        char *val;
        val = (char *) malloc(10000* sizeof(char));
        val = getenv("USER");
	strcat(stre,val);
	strcat(stre,"@");
        char *va;
        va = (char *) malloc(10000* sizeof(char));
        gethostname(va,10000);
	strcat(stre,va);
	strcat(stre,":~");
	strcat(stre,t);
	printf("%s>",stre);
	free(stre);

}

int parse(char *buffer){
	extern char *part[1000];
        char *parts[10000];
        long long int ok = 1,i=0;
	int j = 0;

        while( ok==1 ){
        parts[i]=strsep(&buffer," ");

        if(parts[i]!=NULL){
                if(parts[i][0]!='\0'){
	                part[j]=parts[i];
			j++;

                }
        }
        else{
	       ok=0;

        }

        i++;
        }
	return j;
}

int parsecolon(char *buffer){
	extern char *subcolon[1000];
        char *parts[10000];
        long long int ok = 1,i=0;
        int j = 0;

        while( ok==1 ){
        parts[i]=strsep(&buffer,";");
        if(parts[i]!=NULL){
                if(parts[i][0]!='\0'){
                        subcolon[j]=parts[i];
                        j++;

                }
        }
        else{
		ok=0;

        }

        i++;
        }
        return j;
}

int parsepipe(char *buffer){
        extern char *subpipe[1000];
        char *parts[10000];
        long long int ok = 1,i=0;
        int j = 0;

        while( ok==1 ){
        parts[i]=strsep(&buffer,"|");
        if(parts[i]!=NULL){
                if(parts[i][0]!='\0'){
                        subpipe[j]=parts[i];
                        j++;

                }
        }
        else{
                ok=0;

        }

        i++;
        }
        return j;
}




