#ifndef PROMPTPARSE_H
#define PROMPTPARSE_H

void prompt(char tr[]);
int parse(char *buffer);
int parsecolon(char *buffer);
int parsepipe(char *m);

#endif
