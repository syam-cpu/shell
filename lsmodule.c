#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include "lsmodule.h"
#include "lsmodule.h"
#include<dirent.h>
#include<stdlib.h>
void details(char *p){
   struct stat sfile;
   stat(p, &sfile);
//   perror("fffffff");
 (sfile.st_mode & S_IFDIR)>0 ? printf("d"):printf("-");
  (sfile.st_mode & S_IRUSR)>0 ? printf("r"):printf("-");
  (sfile.st_mode & S_IWUSR)>0 ? printf("w"):printf("-");
  (sfile.st_mode & S_IXUSR)>0 ? printf("x"):printf("-");
  (sfile.st_mode & S_IRGRP)>0 ? printf("r"):printf("-");
  (sfile.st_mode & S_IWGRP)>0 ? printf("w"):printf("-");
  (sfile.st_mode & S_IXGRP)>0 ? printf("x"):printf("-");
  (sfile.st_mode & S_IROTH)>0 ? printf("r"):printf("-");
  (sfile.st_mode & S_IWOTH)>0 ? printf("w"):printf("-");
  (sfile.st_mode & S_IXOTH)>0 ? printf("x"):printf("-");
  printf("  ");
 printf("%2u  ",(unsigned int)sfile.st_nlink);
  struct passwd *us = getpwuid(sfile.st_uid);
  struct group *gr = getgrgid(sfile.st_gid);
 printf("%11s  ",us->pw_name);
 printf("%11s  ",gr->gr_name); 
printf("%2u  ",(unsigned int)sfile.st_nlink);
 printf("%10ld  ",sfile.st_size);
 char time[50];  
 char month[50];
 strftime(time, 50, "%H:%M", localtime(&sfile.st_mtime));
 strftime(month,50,"%m",localtime(&sfile.st_mtime));
 if(strcmp(month,"01")==0)printf("Jan");
 if(strcmp(month,"02")==0)printf("Feb");
 if(strcmp(month,"03")==0)printf("Mar");
 if(strcmp(month,"04")==0)printf("Apr");
 if(strcmp(month,"05")==0)printf("May");
 if(strcmp(month,"06")==0)printf("Jun");
 if(strcmp(month,"07")==0)printf("Jul");
 if(strcmp(month,"08")==0)printf("Aug");
 if(strcmp(month,"09")==0)printf("Sep");
 if(strcmp(month,"10")==0)printf("Oct");
 if(strcmp(month,"11")==0)printf("Nov");
 if(strcmp(month,"12")==0)printf("Dec");
        printf("%10s ",time);
	printf("%20s\n",p);
}
void noa (char *p){
	struct dirent **namelist;
        int n = scandir(p,&namelist,NULL,alphasort);
	if(n==-1){
//	 perror("error:");
	}
        for(int i =0;i<n;i++){
                if(namelist[i]->d_name[0]!='.')
        printf("%s\n",namelist[i]->d_name);
        free(namelist[i]);
        }
}
void yesa (char *p){
	struct dirent **namelist;
        int n = scandir(p,&namelist,NULL,alphasort);
       // perror("error:");
        for(int i =0;i<n;i++){
        printf("%s\n",namelist[i]->d_name);
        free(namelist[i]);
        }
}

void lsmodule(){
	extern char *part[1000];
	extern int nop;
	char *curdir;
	char *pref;
	char *val;
	curdir = (char*) malloc(10000 * sizeof(char));
	getcwd(curdir,1024);
	int okl=0;
	int oka=0;
	int okal = 0;
	int k=0;
	char *par[1000];

	for(int i =1;i<nop-1;i++){
		if(strcmp(part[i],"-a")==0)oka=1;
		else if(strcmp(part[i],"-l")==0)okl=1;
		else if(strcmp(part[i],"-al")==0 || strcmp(part[i],"-la")==0) okal=1;
		else {
			par[k]=(char *) malloc(10000*sizeof(char));
			if(strcmp(part[i],"\0")!=0){
			strcpy(par[k],part[i]);
			k++;
			}
		}
	}
        val = strsep(&part[nop-1],"\n");
	if(strcmp(val,"-a")==0)oka=1;
        else if(strcmp(val,"-l")==0)okl=1;
	else if(strcmp(val,"-al")==0 || strcmp(val,"-la")==0) okal=1;
        else {
                 par[k]=(char *) malloc(10000*sizeof(char));
		 if(strcmp(val,"\0")!=0){
		 strcpy(par[k],val);
                 k++;
		 }
             }
//	printf("ls ra bujji %d\n",k);


        if(nop==1){
	noa(curdir);
	}
	else if(strcmp(part[0],"ls")==0 && strcmp(val,"\0")==0 && nop==2){
		 noa(curdir);
	}
	else if(okl==0 && okal==0){
		if(k){
		for(int i=0 ; i<k ;i++){
			  printf("%s:\n",par[i]);

			if(strcmp(par[i],"~")==0){
				strcpy(par[i],"..");
			}
			if(oka == 0){
				noa(par[i]);
			}
			else{
				yesa(par[i]);
			}
		}}
		else{
		

		if(oka==0)noa(curdir);
		else yesa(curdir);
		}
		}
	else{
		if(k==0){
			struct dirent **namelist;
        int n = scandir(curdir,&namelist,NULL,alphasort);
	if(n==-1){
        perror("error:");
	}
        for(int i =0;i<n;i++){
                if(namelist[i]->d_name[0]!='.' || oka ==1 || okal==1){
                        details(namelist[i]->d_name);
                }
        free(namelist[i]);
        }
	}
	else{
	for(int j =0;j<k;j++){
	struct dirent **namelist;
	  printf("%s:\n",par[j]);
	    
      if(strcmp(par[j],"~")==0){
              strcpy(par[j],"..");
      }




        int n = scandir(par[j],&namelist,NULL,alphasort);
	
	if(n==-1){
        perror("error:");
	}
    
	if(okl==0){
        for(int i =0;i<n;i++){
                if(namelist[i]->d_name[0]!='.' || oka ==1 || okal ==1){
	
		
			details(namelist[i]->d_name);
		}
		
        free(namelist[i]);

        }
	}
	else{
	
		noa(par[j]);
     


	}
	
	}
	}
	
		
	}


}




