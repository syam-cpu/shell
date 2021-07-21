#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include "systemmodule.h"
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<math.h>

char *name;

int converter(char *p){
	int k = strlen(p);
	int ans = 0;
	for(int i = k-1;i>=0;i--){
		int t = int(p[i]-48);
		ans += t * pow(10,k-1-i);
	}
	return ans;
}

void jobs(){
	struct node *temp;
	extern struct node *head;
	temp = head;

	if(head==NULL)printf("NO JOBS CURRENTLY \n");
	while(head!=NULL){
		int statu;
		printf("[%d]",head->jobvalue);
		char *f = strsep(&(head->names),"\n");
		head->names = f;

		char *pref;
		pref = (char *) malloc(10000 * sizeof(char));
		strcpy(pref,"/proc");
		char *suff;
		suff = (char *) malloc(10000 * sizeof(char));
		sprintf(suff,"%d",head->pidvalue);
		strcat(pref,"/");
		strcat(pref,suff);
		strcat(pref,"/stat");
		
		int fd1 = open (pref, O_RDONLY);
		char *data;
		data = (char *) malloc(10000 * sizeof(char));
                 read (fd1,data, 10000);
		
		 char *subfile[1000];
		 int oks = 1;
		 char *parts[10000];
		 int i=0,j=0;
		  while( oks==1 ){
                  parts[i]=strsep(&data," ");

                if(parts[i]!=NULL){
                        if(parts[i][0]!='\0'){
                                 subfile[j]=parts[i];
                                      j++;

                                    }
                         }
                 else{
                        oks=0;

                           }

                        i++;
                 } 

		 
		 
		  if(strcmp(subfile[2],"R")==0){
			  printf("is Running ");
		  }
			  else{
				  printf("is Stopped ");
			  }
	
		
		printf("%s ",f);

		printf(" [%d]\n",head->pidvalue);




		head = head->next;
	}
	head = temp;


}
void getname(int pid){

	struct node *temp;
	extern struct node *head;
	temp = head;
	while(head!=NULL){
		if(head->pidvalue == pid){
			char * f=strsep(&(head->names),"\n");
			head->names =f;
			printf("%s ",f);
			printf("with %d ",head->pidvalue);
			head= temp;
			break;
		}
		else{
			head = head->next;

		}
	}


}
void handler(int sig){
	int status;
	int pid = waitpid(-1,&status,WNOHANG);
	if(pid>0){
//	printf("%d \n",pid);


	getname(pid);
	delnode(pid);
	



	if(WIFEXITED(status))
		 printf("exited noramlly\n");
		 else printf("exited abnormally\n");
	}


	
}

void delnode(int pid){
	extern struct node *head;
	extern struct node *last;
         struct node *temp;
            struct node *prev;


            temp = head;
            prev=head;
            extern int jobcount;



        while(last!=NULL){
                if(head->pidvalue == pid){
                        if(prev==temp && head->next == NULL && head!=temp){//only two node
				head = temp;
				head->next = NULL;
				break;
			}
                        else{
				if(temp->next ==NULL){//only one node
					last = NULL;
					prev->next = NULL;
					head = NULL;
					break;


				}
				else{
					if(head!=prev){
                                prev->next = head->next;
				head = temp;
				break;
					}
					else{
						head=head->next;
						if(head==NULL)last =NULL;
						break;


					}
				}
                               
                        }
                }

                else{  
                        prev = head;
                        head = head->next;
		}

        }


}

void kjobs(){
	struct node *temp;
        extern struct node *head;
        temp = head;
	extern char *part[1000];
	int v = converter(part[1]);
	int u =  converter(part[2]);
//	printf("%d",v);
//	printf("%d",u);
	while(temp!=NULL){
		if(temp->jobvalue == v){
			kill(temp->pidvalue,u);
		//	perror("kill rey");

			return;
		}
		else{
			temp=temp->next;


		}
	}
	printf("No such job exists\n");

}
void fgs(){
	 struct node *temp;
        extern struct node *head;
        temp = head;
	extern int parpid;
        extern char *part[1000];
	int v = converter(part[1]);
        while(temp!=NULL){
                if(temp->jobvalue == v){
			
			int  pidnumber = temp -> pidvalue;

extern int piddy ;
piddy  = pidnumber;
tcsetpgrp(0, getpgid(pidnumber));
kill(temp->pidvalue,18);
int statu;
waitpid(getpgid(pidnumber), &statu, WUNTRACED);
//printf("lol");
tcsetpgrp(0, getpgid(parpid));


		

			int k = temp->pidvalue;
			if(WIFEXITED(statu))
			delnode(k);

			piddy = -1;
			

                      
                        return;
                }
                else{
                        temp=temp->next;


                }
        }
        printf("No such job exists\n");

}
void over(){
	struct node *temp;
        extern struct node *head;
        temp = head;
	if(head == NULL)printf("NO JOBS TO KILL\n");
	while(temp!=NULL){
		int k = temp->pidvalue;
		temp = temp->next;
		kill(k,9);
		usleep(500001);
		}

}
void hand(int sig){
	printf("iam\n");
	extern int waiter;
	extern struct node *head;
	 extern struct node *last;
	 extern int piddy;
	 extern char *jobname;
          extern int jobcount;
//	  printf("aaaaaaaaaaaaaaaaaaaaaa%s\n",jobname);
       if(piddy>0){
                 struct node *f;
        f = (struct node *) malloc(sizeof(struct node));
        f->names = jobname ;
        if(head==NULL){
    
                head=f;
        }
        f->jobvalue = jobcount+1;
        jobcount++;
        f->pidvalue =  piddy;
        f->next = NULL;
        if(last!=NULL)last->next = f;
        last = f;
        if(head==NULL){
                printf("bewarse\n");
        }

        }
      
  //     printf("iam out\n");
       waiter = 2;
       extern int parpid;
      // printf("%d",piddy);
     if(piddy>0) 
       kill(piddy,19);

       piddy = -1;
       return;
 
}
void hands(int sig){

	extern int piddy;
	if(piddy >0)
	kill(piddy,9);

	
	return;
}

void bgs(){
	extern char * part[1000];
	  struct node *temp;
        extern struct node *head;
        temp = head;
	int status;
	int v = converter(part[1]);
	while( temp!=NULL ){
		if(temp->jobvalue == v){
			int k = temp->pidvalue;
		
					kill(k,18);
			return ;
		}
		else {
			temp = temp->next ;
		}
	}
	printf("NO SUCH JOB EXISTS\n");


}

void systemmodule(char *t[1000]){
	extern struct node *head;
	extern struct node *last;
	int fdtemp,fd1;
	extern int less,great,dgreat;
extern char *output;
extern char *jobname;
extern int jobcount;

if(jobcount==0){
head = NULL;
last =  NULL;
}

        extern char * part[1000];	
	extern int nop ;

	part[nop]=NULL;
      	char * val;

int ok  = 0;

if(nop>1){
val=strsep(&part[nop-1],"\n");
part[nop-1]=NULL;


if(strcmp(val,"\0")==0){
part[nop-1]=NULL;


int g = strlen(part[nop-2]);

if(part[nop-2][g-1]=='&'){
	ok=1;
	if(g==1)
	part[nop-2]=NULL;
	else{
		part[nop-2][g-1]='\0';
	}
}

}



else{
part[nop-1]=val;
int g= strlen(part[nop-1]);

if(part[nop-1][g-1]=='&'){
	ok=1;
	if(g==1)
	part[nop-1]=NULL;
	else{
		part[nop-1][g-1]='\0';
	}
}

}
}

extern int piddy;
 piddy =fork();

          signal(SIGCHLD,handler);

if(piddy==0){
signal(SIGTTOU, SIG_DFL);
signal(SIGTTIN, SIG_DFL);

	
if(1){
name = (char *) malloc(10000 * sizeof(char));
strcpy(name,part[0]);


setpgid(0,0);
execvp(part[0],part);
}

}

else{
	   // signal(SIGCHLD,handler);


	if(ok!=1){
	int status;

 
extern int waiter;
waiter = -1;
         
	 waiter = waitpid(piddy,&status,WUNTRACED );
//	 printf("aaaaaaaaa");


	}
	if(ok){
		//printf("not came here\n");
		 struct node *f;
        f = (struct node *) malloc(sizeof(struct node));


        f->names = jobname ;
        if(head==NULL){
                head=f;
        } 
      	f->jobvalue = jobcount+1;
        jobcount++;
        f->pidvalue =  piddy;
        f->next = NULL;
        if(last!=NULL)last->next = f;
        last = f;
  
        if(head==NULL){
                printf("bewarse\n");
        }
	piddy =-1;




	}
	

}



}
