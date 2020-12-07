#include "utils.h"

extern struct utsname buffer;
extern ll pidlist[10000][2],pidpt;
extern char input[1000],inp[100][1000],comand[100][1000];
extern char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
extern char pidint[100];
char hist[22][1000];
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


extern v inpu()
{
    const char sp[4]="<";
    strcpy(cpycom,faltu);
    char* bre=strtok(cpycom,sp);
    ll xy=0;
    while(!bre==0)
    {
        strcpy(comc2[xy],bre);
        ++xy;
        bre = strtok(0,sp);
    }
    const char spac[4]=" ";
    char bhag[10][100];
    char* toke;
    toke  =strtok(comc2[0],spac);
    ll ccc=0;
    while(!toke==0)
    {
        strcpy(bhag[ccc],toke);
        ++ccc;
        toke=strtok(0,spac);
    }
    char *args[99];
    for (ll i = 0; i < ccc; ++i)
    {
        args[i]=bhag[i];
    }
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
        while(!tok==0)
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
        if (execvp(args[0], args) < 0)
        {
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
        close(fd);
    }
    else
    {
        wait(NULL);
    }
}

extern v outf()
{
    const char sp[4]=">";
    strcpy(cpycom,faltu);
    char* bre=strtok(cpycom,sp);
    ll xy=0;
    while(!bre==0)
    {
        strcpy(comc2[xy],bre);
        ++xy;
        bre = strtok(0,sp);
    }
    const char spac[4]=" ";
    char bhag[10][100];
    char* toke;
    toke  =strtok(comc2[0],spac);
    ll ccc=0;
    while(!toke==0)
    {
        strcpy(bhag[ccc],toke);
        ++ccc;
        toke=strtok(0,spac);
    }
    char *args[99];
    for (ll i = 0; i < ccc; ++i)
    {
        args[i]=bhag[i];
    }

    args[ccc]= NULL;
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
        while(!tok==0)
        {
            strcpy(bhagwan[cc],tok);
            ++cc;
            tok=strtok(0,space);
        }
        ll fd=creat(bhagwan[0],0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
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

extern v outa()
{
    const char sp[4]=">>";
    strcpy(cpycom,faltu);
    char* bre=strtok(cpycom,sp);
    ll xy=0;
    while(!bre==0)
    {
        strcpy(comc2[xy],bre);
        xy++;
        bre = strtok(0,sp);
    }
    const char spac[4]=" ";
    char bhag[10][100];
    char* toke;
    toke  =strtok(comc2[0],spac);
    ll ccc=0;
    while(!toke==0)
    {
        strcpy(bhag[ccc],toke);
        ++ccc;
        toke=strtok(0,spac);
    }
    char *args[99];
    for (ll i = 0; i < ccc; ++i)
    {
        args[i]=bhag[i];
    }
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
        while(!tok==0)
        {
            strcpy(bhagwan[cc],tok);
            ++cc;
            tok=strtok(0,space);
        }
        ll fd=open(bhagwan[0],O_APPEND | O_WRONLY);
        if(fd<0)
        {
            fd=creat(bhagwan[0],0644);
        }
        dup2(fd, STDOUT_FILENO);
        if (execvp(args[0], args) < 0)
        {
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
        close(fd);
    }
    else
    {
        wait(NULL);
    }
}

extern v aab()
{
    const char ar[4]=">";
    strcpy(cpycom,faltu);
    char left[3][100];
    char *lr=strtok(cpycom,ar);
    ll lll=0;
    while (!lr==0)
    {
        strcpy(left[lll],lr);
        ++lll;
        lr=strtok(0,ar);
    }
    char right[10][100];
    char *rr;
    const char spa[4]=" ";
    rr=strtok(left[1],spa);
    ll ccd=0;
    while(!rr==0)
    {
        strcpy(right[ccd],rr);
        ++ccd;
        rr=strtok(0,spa);
    }

    //
    const char sp[4]="<";
    char cpyco[200];
    strcpy(cpyco,left[0]);
    char* bre=strtok(cpyco,sp);
    ll xy=0;
    while(!bre==0)
    {
        strcpy(comc2[xy],bre);
        ++xy;
        bre = strtok(0,sp);
    }
    const char spac[4]=" ";
    char bhag[10][100];
    char* toke;
    toke  =strtok(comc2[0],spac);
    ll ccc=0;
    while(!toke==0)
    {
        strcpy(bhag[ccc],toke);
        ++ccc;
        toke=strtok(0,spac);
    }
    char *args[]={bhag[0],NULL};
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
        while(!tok==0)
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
        ll final=creat(right[0],0644);
        dup2(fd, STDIN_FILENO);
        dup2(final,STDOUT_FILENO);
        close(fd);
        close(final);
        if (execvp(args[0], args) < 0)
        {
            printf("ERROR: exec failed\n");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }

}

extern v abb()
{
    const char ar[4]=">>";
    strcpy(cpycom,faltu);
    char left[3][100];
    char *lr=strtok(cpycom,ar);
    ll lll=0;
    while (!lr==0)
    {
        strcpy(left[lll],lr);
        ++lll;
        lr=strtok(0,ar);
    }
    const char spa[4]=" ";
    char right[10][100];
    char *rr;
    rr=strtok(left[1],spa);
    ll ccd=0;
    while(!rr==0)
    {
        strcpy(right[ccd],rr);
        ++ccd;
        rr=strtok(0,spa);
    }

    const char sp[4]="<";
    char cpyco[200];
    strcpy(cpyco,left[0]);
    char* bre=strtok(cpyco,sp);
    ll xy=0;
    while(!bre==0)
    {
        strcpy(comc2[xy],bre);
        ++xy;
        bre = strtok(0,sp);
    }
    const char spac[4]=" ";
    char bhag[10][100];
    char* toke;
    toke  =strtok(comc2[0],spac);
    ll ccc=0;
    while(!toke==0)
    {
        strcpy(bhag[ccc],toke);
        ++ccc;
        toke=strtok(0,spac);
    }
    char *args[]={bhag[0],NULL};
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
        while(!tok==0)
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
        close(fd);
        ll final=open(right[0],O_APPEND | O_WRONLY);
        if(final<0)
        {
            ll final=creat(right[0],0644);
        }
        dup2(final,STDOUT_FILENO);
        close(final);
        if (execvp(args[0], args) < 0)
        {
            printf("ERROR: exec failed\n");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }

}
