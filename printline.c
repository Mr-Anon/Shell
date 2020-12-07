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

extern void printline()
{
   
    printf("<%s@%s:",buffer.nodename,buffer.sysname);
    
    ll fl=0;
    for(ll i=0;i<strlen(odir);++i)
    {
        if(adir[i]!=odir[i])
        {
            fl=1;
            break;
        }
    }
    if(fl==0)
    {
        printf("~");
        for(ll i=strlen(odir);i<strlen(adir);++i)
        {
            printf("%c",adir[i]);
        }
    }
    else
    {
        printf("%s",adir);
    }
    
    printf("> ");
}
