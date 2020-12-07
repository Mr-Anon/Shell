#include "utils.h"


extern struct utsname buffer;
extern ll pidlist[10000][2],pidpt;
extern char input[1000],inp[100][1000],comand[100][1000];
extern char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
extern char pidint[100];
extern char pidls[1000][200];
extern char comc2[2][500],cpycom[1000];


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

extern v jobs()
{
    for(ll i=0;i<pidpt;++i)
    {
        if(pidlist[i][0]==0)
        {
            ll pid=pidlist[i][1];
            char pi[100]="/proc/";
            ll temp=pid;
            ll ptr=0;
            while(temp)
            {
                pidint[ptr]=48+temp%10;
                temp/=10;
                ++ptr;
            }
            pidint[ptr]='\0';
            strrevpid();
            strcat(pi,pidint);
            strcat(pi,"/stat");
            FILE *fptr;
            fptr = fopen(pi, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
            }
            char fl[1000];
            char ag[100][200];
            fscanf(fptr,"%[^\n]", fl);
            char* bre;
            const char sp[4]=" ";
            ll comcc=0;
            bre = strtok(fl,sp);
            while(bre != 0)
            {
                strcpy(ag[comcc],bre);
                comcc++;
                bre = strtok(0,sp);
            }
             char *status1 = (char *)malloc(1024*sizeof(char));
            if(strcmp(ag[2],"I")==0)
            {
                strcpy(status1,"Interrupted");
            }
            else if(strcmp(ag[2],"T")==0)
            {
                strcpy(status1,"Stopped");
            }
            else
            {
                strcpy(status1,"Running");
            }
            printf("[%d] %s %s [%d]\n",i,status1,pidls[i],pidlist[i][1] );;
        }
    }
}

extern v kjob()
{

    for(ll i=0;i<pidpt;++i)
    {
      if(i==atoi(comand[1]))
      {
        kill(pidlist[i][1],atoi(comand[2]));
        if(!strcmp(comand[2],"9"))
        {
            pidlist[i][0]=1;
        }
        break;
      }
    }
}

extern v bg()
{
	pid_t ppid;
	for(ll i=0;i<pidpt;++i)
	{
		if(i==atoi(comand[1]))
		{
			kill(pidlist[i][1],SIGCONT);
			break;
		}
	}
}

extern v fg()
{
	

  ll pidS = pidlist[atoi(comand[1])][1];
  tcsetpgrp(0,pidS);
  kill(pidS,SIGCONT);
  waitpid(pidS, NULL, WUNTRACED);
  signal(SIGTTOU, SIG_IGN);
  tcsetpgrp(0,getpid());
  signal(SIGTTOU, SIG_DFL);

}


extern v overkill()
{
    for(ll i=0;i<pidpt;++i)
    {
        if(pidlist[i][0]=1)
        {
            kill(pidlist[i][1],9);
            pidlist[i][0]=1;
        }
    }
}