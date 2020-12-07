#include "utils.h"
struct utsname buffer;
char input[1000],inp[100][1000],comand[100][1000],adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
char pidint[100];
#define l int
v printline();
v echo();
v pwd();
v cd(char* inpp);
l checkdir();
v ls(l comc);
l rd();
v printinfo(char* path,char* list);
v pinfo(l comc);
v strrevpid();
v restall(l comc);

extern v pinfo(l comc)
{
    l pid;
    char pi[100]="/proc/";
   if(comc==1)
    {
        pid=getpid();
    l ptr=0;
    while(pid)
    {
        pidint[ptr]=48+pid%10;
        pid/=10;
        ++ptr;
    }
    pidint[ptr]='\0';
    strrevpid();
    strcat(pi,pidint);
    printf("%s\n",pidint );
  }
  else
  {
    printf("PID-- %s\n",comand[1] );
    strcat(pi,comand[1]);
  }
    char pidpath[100],second[100];
    strcpy(second,pi);
    strcat(pi,"/maps") ,strcat(second,"/stat");
    FILE *fptr;
    fptr = fopen(pi, "r");// returns file stream pointer
  
    if (fptr == NULL)
    {
        printf("No such process \n");
        return;
    }
    char fl[1000],ag[100][200];
    fscanf(fptr,"%[^\n]", fl);
    char* bre;
    const char sp[4]=" ";
    bre = strtok(fl,sp);
    l comcc=0;
    while(!bre== 0)
    {
        strcpy(ag[comcc],bre);
        ++comcc;
        bre = strtok(0,sp);
    }
    printf("Path--%s\n",ag[5] );
    fptr=fopen(second,"r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
    }
    fscanf(fptr,"%[^\n]", fl);
    bre = strtok(fl,sp);
    comcc=0;
    while(!bre==0)
    {
        strcpy(ag[comcc],bre);
        ++comcc;
        bre = strtok(0,sp);
    }
    printf("Process Status -- %s\n",ag[2]);
    printf("memory ​ --%s\n",ag[22] );
}


v strrevpid()
{
    l nn=strlen(pidint);
    for(l i=0;i<nn/2;++i)
    {
        char lul=pidint[i];
        pidint[i]=pidint[nn-1-i];
        pidint[nn-1-i]=lul;
    }
}