

#include "utils.h"

extern struct utsname buffer;//for user name
ll pidlist[1000][2],pidpt;
extern char input[1000],inp[100][1000],comand[100][1000];
extern char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
char pidls[1000][200];
extern pid_t pid;
char* fgname;
ll fgprocess;
v printline();
v echo();
v pwd();
v cd(char* inpp);
ll checkdir();
v ls(ll comc);
ll rd();
v prllinfo(char* path,char* list);
v pinfo(ll comc);
v strrevpid();
v bakisab(ll comc);
v back(ll comc);


extern v bakisab(ll comc)
{
    char *args[1000];
    for(ll i=0;i<comc;++i)
    {
        args[i]=comand[i];
    }
    args[comc]=NULL;
    if((pid = fork()) < 0)
    {
            printf("*** ERROR: forking child process failed\n");
            exit(1);
    }
    else if (pid==0)
    {
          if (execvp(args[0], args) < 0)
          {
                printf("*** ERROR: exec failed\n");
                exit(1);
            }
        }
    else
      {
        fgname=(char*)malloc(strlen(args[0]+1));
        strcpy(fgname, args[0]);
        fgprocess=pid;
        //printf("%d", fgprocess);
        fflush(stdout);
        waitpid(pid, NULL, WUNTRACED);
      }
    }

extern v back(ll comc)
{
  char *args[1000];
  for(ll i=0;i<comc-1;++i)
  {
      args[i]=comand[i];
  }
  args[comc-1]=NULL;
  pid_t cid = fork();
    if(cid==0)
    {
          setpgid(0,0);
          execvp(args[0],args);
    }
    else
    {     
          printf("pid=%d\n",cid );
          pidlist[pidpt][1]=cid;
          strcpy(pidls[pidpt],faltu);
          ++pidpt;
    }

}
