#ifndef SYSTEMMODULE_H
#define SYSTEMMODULE_H
struct node {
        char *names;
        int pidvalue;
        char *stateofprocess[10000];
        struct node * next;
        int jobvalue;


};
void systemmodule(char *t[1000]);
void jobs();
void kjobs();
void fgs();
void delnode(int pid);
void over();
void hand(int sig);
void bgs();
void hands(int sig);
void adjustjobcount();


#endif
