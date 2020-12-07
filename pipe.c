#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#define ll int 
#define v void

extern struct utsname buffer;//for user name
extern char input[1000],inp[100][1000],comand[100][1000];
extern char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
extern char pidint[100];
char hist[22][1000];
extern ll pidlist[10000][2],pidpt;
extern char pidls[1000][200];
char comc2[2][500],cpycom[1000];

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
v back(ll comc);
v pidover();
v piping();
v inpu();
v outa();
v outf();
v aab();
v abb();

char nali[100][1000];
ll tempi,tempo;

extern v  piping()
{
    const char pi[4]="|";
    char *bre=strtok(faltu,pi);
    ll numpi=0;
    while(!(bre==NULL))
    {
        strcpy(nali[numpi],bre);
        ++numpi;
        bre=strtok(0,pi);
    }
    remove("tempo.temp");
    for(ll i=0;i<numpi;++i)
    {
        ll osr=0,odr=0,ir=0;
        for(ll j=0;j<strlen(nali[i])-1;++j)
        {
            if(faltu[j]=='>' && faltu[j+1]=='>')
            {
                odr=j;
                ++j;
            }
            if(faltu[j]=='>' && faltu[j+1]!='>')
            {
                osr=j;
            }
            if(faltu[j]=='<')
            {
                ir=1;
            }
        }
        if(ir==0 && osr==0 && odr!=0)
        {
            remove("tempo.temp");
            strcpy(faltu,nali[i]);
            outa();
        }
        else if(ir==0 && osr!=0 && odr==0)
        {
          remove("tempo.temp");
          strcpy(faltu,nali[i]);
          outf();
        }
        else if(ir!=0 && osr==0 && odr==0)
        {
            const char sp[4]="<";
            char pipeke[10][100];
            char* bre=strtok(nali[i],sp);
            ll xy=0;
            while(!(bre==NULL))
            {
                strcpy(pipeke[xy],bre);
                ++xy;
                bre = strtok(0,sp);
            }
            const char spac[4]=" ";
            char bhag[10][100];
            char* toke;
            toke  =strtok(pipeke[0],spac);
            ll ccc=0;
            while(!(toke==NULL))
            {
                strcpy(bhag[ccc],toke);
                ++ccc;
                toke=strtok(0,spac);
            }
            char *args[1000];
            for(ll i=0;i<ccc;++i)
            {
                args[i]=bhag[i];
            }
            args[ccc]=NULL;
            pid_t pid;
            if ((pid = fork()) < 0)
            {
                printf("*** ERROR: forking child process failed\n");
                exit(1);
            }
            else if (pid == 0)
            {
                const char space[4]=" ";
                char bhagwan[10][100];
                char* tok;
                tok=strtok(comc2[1],space);
                ll cc=0;
                while(!(tok==NULL))
                {
                    strcpy(bhagwan[cc],tok);
                    ++cc;
                    tok=strtok(0,space);
                }
                ll fd=open(bhagwan[0],O_RDONLY, 0);
                if(fd<0)
                {
                    printf("File not present\n");
                }
                dup2(fd, STDIN_FILENO);
                tempo = creat("tempo.temp",0777);
                dup2(tempo,STDOUT_FILENO);
                close(fd);
                close(tempo);
                if (execvp(args[0], args) < 0)
                {
                    printf("*** ERROR: exec failed\n");
                    exit(1);
                }
            }
            else
            {
                wait(NULL);
            }
        }
        else if(ir!=0 && osr!=0 && !odr)
        {
            if(ir>osr)
            {
                printf(":(" );
            }
            else
            {
                strcpy(faltu,nali[i]);
                remove("tempo.temp");
                aab();
            }
        }
        else if(ir!=0 && !osr && odr!=0)
        {
            if(ir>odr)
            {
                printf(":(" );
            }
            else
            {
                strcpy(faltu,nali[i]);
                remove("tempo.temp");
                abb();
            }
        }
        else
        {
            const char spac[4]=" ";
            char bhag[10][100];
            char* toke;
            toke=strtok(nali[i],spac);
            ll ccc=0;
            while(!(toke==NULL))
            {
                strcpy(bhag[ccc],toke);
                ++ccc;
                toke=strtok(0,spac);
            }
            char *args[1000];
            for(ll i=0;i<ccc;++i)
            {
                args[i]=bhag[i];
            }
            args[ccc]=NULL;

            pid_t pid;
            if ((pid = fork()) < 0)
            {
                printf("*** ERROR: forking child process failed\n");
                exit(1);
            }
            else if (pid == 0)
            {
                if(i!=0)
                {
                    tempo=open("tempo.temp", O_RDONLY);
                    dup2(tempo, STDIN_FILENO);
                    close(tempo);
                    remove("tempo.temp");
                }
                if(numpi-1>i)
                {
                    //printf("out ka dup hua\n");
                    tempo = creat("tempo.temp",0777);
                    dup2(tempo,STDOUT_FILENO);
                    close(tempo);
                }
                //printf("YASS\n");
                if (execvp(args[0], args) < 0)
                {
                    printf("*** ERROR: exec failed lul %s\n",args[0]);
                    exit(1);
                }
            }
            else
            {
                wait(NULL);
            }
        }
    }
    remove("tempo.temp");
}