#include "nightmodule.h"
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
void nightmodule(){
	extern char *part[1000];

 char * filecon;


        pid_t pid = fork();

if(pid==0){
	int delay;
char x = part[2][0];
 delay=int(x)-48;
			
        while(1){

        sleep(delay);
        int fd1 = open ("/proc/loadavg", O_RDONLY);
        filecon = (char *) malloc(10000 * sizeof(char));
        read (fd1, filecon, 1000);

        char *partss[1000];
        char *parts[10000];
        long long int ok = 1,i=0;
        int j = 0;

        while( ok==1 ){
        parts[i]=strsep(&filecon," ");

        if(parts[i]!=NULL){
                if(parts[i][0]!='\0'){
                       partss[j]=parts[i];
                        j++;

                }
        }
        else{
                ok=0;
        }

        i++;
        }

        printf("%s",partss[4]);
        close(fd1);
        free(filecon);
        }

 }
 else{
                while(1){
			char *b;
                b = (char *)malloc(100000 * sizeof(char));
                size_t bufsize = 100000;
                getline(&b,&bufsize,stdin);

		
                /*if(getchar()=='q'){
                        kill(pid,SIGINT);
                        break;

                }*/
		if(strcmp(b,"q\n")==0){
			kill(pid,SIGINT);
			break;
		}

                }

        }
}

