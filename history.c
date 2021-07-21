#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>

void history(char *dd,int a){
	extern char * pref;
	char *u ;
	u = (char *) malloc(10000 * sizeof(char));
	strcpy(u,pref);
	strcat(u,"/history.txt");

           int fd1 = open (u, O_RDWR);
	   int fd3;
	   if(fd1==-1){
		    fd3 = open (u, O_RDWR | O_CREAT | O_TRUNC, 0777);
	   }
	   char *k;
	   k = (char *) malloc(100000 * sizeof(char));
	   read(fd1,k,10000);
	char *partsss[1000];
        char *parts[10000];
        long long int ok = 1,i=0;
        int j = 0;

        while( ok==1){
        parts[i]=strsep(&k,"\n");

        if(parts[i]!=NULL){
                if(parts[i][0]!='\0'){
                       partsss[j]=parts[i];
		       

                        j++;

                }
        }
        else{
                ok=0;
        }

        i++;
        }
	
/*	for(int i=0;i<j;i++){
		printf("%s\n",partsss[i]);
	//	strcat(partsss[i],"\n");
	}*/
	if(a==0){
	if(j==20){
	
		 int fd2 = open (u, O_RDWR | O_CREAT | O_TRUNC, 0777);
		 for(i=1;i<20;i++){
			 write (fd2, partsss[i], strlen(partsss[i]));
			 write(fd2,"\n",1);
					 }
					 write(fd2,dd,strlen(dd));
					 write(fd2,"\n",1);
	}
	else{
		if(fd1!=-1){
		write(fd1,dd,strlen(dd));
				j++;
		}
		else{
			write(fd3,dd,strlen(dd));
			j++;
		}


	}
	}

	if(a==1){
//		printf("dddddddddddddddddddddddddddDD");
		int g ;
		if(j-10<0){
			g=0;
		}
		else{
			g=j-10;
		}
			
		for(i=g; i<=j-1;i++){
		printf("%s\n",partsss[i]);
		}
		}
	
	



}
          




