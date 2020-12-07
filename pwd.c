#include "utils.h"

struct utsname buffer;
char pidint[100];
char input[1000],inp[100][1000],comand[100][1000];
char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];

v printline();
v echo();
v pwd();
v cd(char* inpp);
ll checkdir();
v ls(ll comc);
ll rd();
v printinfo(char* path,char* list);
v pinfo(ll comc);
v strrevpid();
v bakisab(ll comc);

extern v pwd()
{
    printf("%s\n",adir);
}
