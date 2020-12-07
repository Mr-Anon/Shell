#include "utils.h"
ll isZombie();
extern struct utsname buffer;
extern ll pidlist[10000][2],pidpt;
extern char input[1000],inp[100][1000],comand[100][1000];
extern char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
extern char pidint[100];
ll totk=0;
ll fgprocess;
extern char pidls[1000][200];
extern char comc2[2][500],cpycom[1000];
ll osr=0,odr=0,ir=0,pip=0;
pid_t pid;

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
char* fgname;
v pidover();
v piping();
v inpu();
v outa();
v outf();
v aab();
v abb();
v jobs();
v viv_sigint(ll sig_num);
v kjob();
v overkill();
v fg();
v bg();

static void handle_sigstop(int sig) 
{
    if(fgprocess!=-1)
    {
                pidlist[pidpt][1]=fgprocess;
                strcpy(pidls[pidpt],fgname);
                ++pidpt;
                kill(fgprocess, SIGSTOP);
                printf("%d", setpgid(fgprocess, 0));
    
    fgprocess=-1;
    }
}
ll main()
{
    pidpt=0;
    getcwd(adir,1000);
    getcwd(odir,1000);
    uname(&buffer);
    while(1)
    {

        struct sigaction sb = {0};
        sb.sa_handler = handle_sigstop;
        sb.sa_flags = SA_NODEFER;
        sigemptyset(&sb.sa_mask);
        sigaction(SIGTSTP, &sb, 0);
        fgprocess=-1;
        signal(SIGINT, viv_sigint);
     
        pidover();
        printline();
        if(scanf("%[^\n]s",input)==EOF)
        {
            
            exit(0);
        }
     
        char* tok;
        const char del[4]=";";
        tok = strtok(input,del);
        ll comandCount=0;
        while(tok != 0)
        {
            //printf(" %s\n", tok);
            strcpy(inp[comandCount],tok);
            ++comandCount;
            tok = strtok(0,del);
        }
        
        for(ll i=0;i<comandCount;++i)
        {
            char* bre;
            ll  status;
            const char sp[4]=" ";
          
            strcpy(faltu,inp[i]);
         
            ++totk;
            bre = strtok(inp[i],sp);
            ll comc=0;
            while(bre != 0)
            {
                strcpy(comand[comc],bre);
                ++comc;
                bre = strtok(0,sp);
            }
            osr=0,odr=0,ir=0,pip=0;
            for(ll i=0;i<strlen(faltu)-1;++i)
            {
                if(faltu[i]=='|')
                    pip=i;
                if(faltu[i]=='>' && faltu[i+1]!='>')
                    osr=i;
                
                if(faltu[i]=='>' && faltu[i+1]=='>')
                {
                    odr=i;
                    ++i;
                }
                if(faltu[i]=='<')
                {
                    ir=1;
                }
            }
            if(pip)
            {
                piping();
            }
            else if(ir!=0 && osr==0 && odr==0)
            {
                inpu();
            }
            else if(ir==0 && osr!=0 && odr==0)
            {
                outf();//over write
            }
            else if(ir==0 && osr==0 && odr!=0)
            {
                outa();//append
            }
            else if(ir!=0 && osr!=0 && !odr)
            {
                if(ir>osr)
                {
                    printf(":(" );
                }
                else
                {
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
                    abb();
                }
            }
            else
            {
                if(!strcmp(comand[0],"echo"))
                {
                    for(ll i=1;i<comc;++i)
                    {
                        printf("%s ",comand[i]);
                    }
                    printf("\n");
                }
                else if(!strcmp(comand[0],"pwd"))
                {
                    pwd();
                }
                else if(!strcmp(comand[0],"cd"))
                {
                    if(comc==1)
                    {
                        strcpy(adir,odir);
                        chdir(adir);
                    }
                    else
                    {
                        cd(comand[1]);
                    }
                }
                else if(!strcmp(comand[0],"ls"))
                {
                    ls(comc);
                }
                else if(!strcmp(comand[0],"pinfo"))
                {
                    pinfo(comc);
                }
                
                else if (!strcmp(comand[0],"setenv"))
                {
                    if(comc==1)
                    {
                        printf("Too few comands\n");
                    }
                    else if (comc>3)
                    {
                        printf("Too many comands\n");
                    }
                    else
                    {
                        if (comand[2] == NULL)
                        {
                            strcpy(comand[2]," ");
                        }
                        if (setenv(comand[1],comand[2],1) != 0)
                        {
                            perror("shell");
                        }
                    }
                }
                else if (!strcmp(comand[0],"unsetenv"))
                {
                    if(comc==1||comc>2)
                    {
                        printf("Too few or many comands\n");
                    }
                    else if(unsetenv(comand[1]) != 0)
                    {
                        perror("shell");
                    }
                }
                else if (!strcmp(comand[0],"jobs"))
                {
                    jobs();
                }
                else if (!strcmp(comand[0],"kjob"))
                {
                    kjob();
                }
                else if (!strcmp(comand[0],"overkill"))
                {
                    overkill();
                }
                else if(!strcmp(comand[0],"quit"))
                {
                    kill(getpid(),9);
                }
                else if (!strcmp(comand[0],"fg"))
                {
                    fg();
                }
                else if (!strcmp(comand[0],"bg"))
                {
                    bg();
                }
              
                else if (strcmp(comand[comc-1],"&"))
                {
                    bakisab(comc);
                }
                else
                {
                    back(comc);
                }
            }
        }
       

        getchar();
        fflush(stdin);
        fflush(stdout);
    }
}



v pidover()
{
    for(ll i=0;i<pidpt;++i)
    {
        if(pidlist[i][0]==0)
        {
            if(!kill(pidlist[i][1],0)==0)
            {
                printf("%s with pid %d exited \n",pidls[i],pidlist[i][1] );
                pidlist[i][0]=1;
            }
        }
    }
}

v viv_sigint(ll sig_num)
{
    signal(SIGINT, viv_sigint);
  
    fflush(stdout);
}
