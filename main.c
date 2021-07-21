#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "prompt_n_parse.h"
#include "lsmodule.h"
#include<unistd.h>
#include "systemmodule.h"
#include "inbuilt.h"
#include "pinfomodule.h"
#include "nightmodule.h"
#include "history.h"
#include <signal.h>

int parpid;
char *jobname ;
char *part[1000];
int nop;
char *str;
char *pref;
char *subcolon[10000];
int less=0,great=0,dgreat=0;
char *output;
char * subpipe[10000];
int stdouts = dup(1);
int stdins  = dup(0);
int jobcount=0;

struct node *last;
struct node *head;
int piddy;
int waiter;


int main(){
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	//  signal(SIGCHLD,handler);



	signal(SIGTSTP,hand);
	signal(SIGINT,hands);
	head = NULL;
	last = NULL;
	parpid = getpid();
        str = (char *) malloc(10000 * sizeof(char));
	pref = (char *) malloc(10000 * sizeof(char));
	getcwd(pref,1024);
	char c[1] ="";
	str[0]='\0';
	char tr[10000]="";
	
	while(1){
		prompt(tr);

		char *buffer;
		buffer = (char *)malloc(100000 * sizeof(char));
		size_t bufsize = 100000;

		getline(&buffer,&bufsize,stdin);
		
		if(strcmp(buffer,"\0")==0){
			printf("\n");
			exit(0);
		}
		

		history(buffer,0);

		int d=parsecolon(buffer);      
	
                                      
		for(int i = 0;i < d ;i++){

			char *m;
			m = (char *)  malloc(100000 * sizeof(char));
			strcpy(m,subcolon[i]);

		int numberofsubpipes = parsepipe(subcolon[i]);
		int fd[2];
		stdouts = dup(1);
		int f;
		f = 3;
		for(int sec = 0;sec < numberofsubpipes ; sec++){
			jobname = (char *) malloc(10000 * sizeof(char));
			strcpy(jobname,subpipe[sec]);
		//	printf("%s\n",jobname);
			//signal(SIGTSTP,hand);


		nop = parse(subpipe[sec]);
		                char *copies ;
                copies = (char *) malloc(10000 * sizeof(char));
                strcpy(copies,part[nop-1]);
                char *vale;
                vale = strsep(&copies,"\n");


                strcpy(part[nop-1],vale);

		pipe(fd);
		if(sec == 0 && numberofsubpipes>1){
			dup2(fd[1],1);
			close(fd[1]);
		}
		else if(numberofsubpipes>1){
			dup2(f,0);
		
			close(f);
			if(sec == numberofsubpipes - 1){
				fflush(stdout);
				dup2(stdouts,1);
				
			}
			else{
				fflush(stdout);
				dup2(fd[1],1);
				close(fd[1]);
				
			}
		}
		f=fd[0]; 

               


		char *newsubpipe;
		newsubpipe = (char *) malloc(10000 * sizeof(char));
		newsubpipe[0]='\0';

		 

		for(int director = 0; director < nop ;director++){
			if(strcmp("<",part[director])==0)
			{
				int input_file_fd = open(part[director+1],O_RDWR);
			
	

				if(input_file_fd == -1)
				{
					perror("kindly give valid file name");
					break;
				}
				 
                               stdins  = dup(0);


				dup2(input_file_fd,0);

				director++;
			}
			else if(strcmp(">",part[director])==0)
			{        stdouts = dup(1);
				    int newoutput = open (part[director+1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                                  
                                    dup2(newoutput,1);
				    
				    
				    break;

			}

			else if(strcmp(">>",part[director])==0)
			{           stdouts = dup(1);
				    int oldfd = open (part[director+1], O_RDWR);
                                    int newfd;
                                    if(oldfd == -1)
				    {
					

                                         newfd = open (part[director+1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                                     
                                         dup2(newfd,1);


                                    }
                                    else
				    {
					     lseek(oldfd,0,SEEK_END);

                           
					 dup2(oldfd,1);


        			    }	
			    break;	    
			}

			else
			{
				strcat(newsubpipe,part[director]);
				strcat(newsubpipe," ");
			}
		}

		



		for(int free=0;free<nop;free++)part[free]=NULL;

	         nop = parse(newsubpipe);	
	if(nop == 0)continue;


                if(strcmp(part[0],"\n")==0){
	
                        continue;
                }
		else if(strcmp(part[0],"quit")==0){
			exit(0);
		}
		

		else if(strcmp(part[0],"ls")==0){
			lsmodule();
		}

		else if((strcmp(part[0],"pinfo")==0 || strcmp(part[0],"pinfo\n")==0) && nop == 1){
		    pid_t pid = getpid();
		    char *mypid;
		    mypid = (char *) malloc(10000 * sizeof(char));
		    sprintf(mypid, "%d", pid);
                    char par[10000] = "/proc/";
                    strcat(par,mypid);
		    pinfomodule(par,0);
		}
		else if(strcmp(part[0],"pinfo")==0 &&strcmp(part[1],"\0")==0){
		    pid_t pid = getpid();
                    char *mypid;
                    mypid = (char *) malloc(10000 * sizeof(char));
		    sprintf(mypid, "%d", pid);
                    char par[10000] = "/proc/";
                    strcat(par,mypid);
                    pinfomodule(par,0);

		}
		else if(strcmp(part[0],"pinfo")==0){
			
		    char par[10000] = "/proc/";
                    strcat(par,part[1]);
                    pinfomodule(par,0);
		   

		}

		else if(strcmp(part[0],"nightswatch")==0 && strcmp(part[1],"-n")==0 && strcmp(part[3],"newborn")==0){
			nightmodule();
		}

		else if(strcmp(part[0],"history")==0){
			history(NULL,1);
		}

		else if(strcmp(part[0],"jobs")==0){
			
			jobs();


		}
		else if(strcmp(part[0],"kjob")==0){
			if(nop!=3){
				printf("provide sufficient number of arguments\n");
			}
			else{
			kjobs();
			}


		}
		else if(strcmp(part[0],"fg")==0){
			if(nop!=2){
				printf("provide sufficient number of arguments\n");
			}
			else{	
		             fgs();
			}
		}
		else if(strcmp(part[0],"bg")==0){
			if(nop!=2){
				printf("provide sufficient number of arguments\n");
			}
			else{
			bgs();
			}
		}
		else if(strcmp(part[0],"overkill")==0){
		
			over();
		}

		else if(strcmp(part[0],"setenv")==0){
			if(nop!=3){
				printf("provide sufficient arguments\n");
			}
			else{
			int g =setenv(part[1],part[2],0);
			if(g==-1)perror("failed");

			}
		}
		else if(strcmp(part[0],"unsetenv")==0){
			if(nop!=2){
				printf("provide sufficient arguments\n");
			}
			else{
				int g = unsetenv(part[1]);
				if(g==-1){
					perror("failed");
				}
	
			}
		}
		else{  
			int one ;
			int f=inbuilt();

			
			
			if(f==0){
			//	printf("%d\n",piddy);
	
				
				systemmodule(part);
				//printf("exitted from systemmodule\n");

	                     }

			}
			

		}
//		printf("ffff");
		dup2(stdins,0);
		dup2(stdouts,1);
		

		for(int dscs=0;dscs<nop;dscs++)part[dscs]=NULL;
		strcpy(tr,str);
		}

	}
}
		
	


	

		
	
