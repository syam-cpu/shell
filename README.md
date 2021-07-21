
run make command to compile my files . then ./a.out to run my file.

main.c sends the commands to corresponding module files 

ls type of commands to  lsmodule.c.

pinfo type to pinfomodule.c

nightswatch to nightmodule.c

history to history.c

cd,echo,pwd inbuilt.c

then to systemmodule.c 

for set env and unset env i used systemcalls corresponding to them

created a linked list of stopped or active bacground process 

if it is completed i will remove node

while displaying jobs i get their status by stat file

to convert bg to running i simply send continue signal

for over kill i am killing every process in linked list


