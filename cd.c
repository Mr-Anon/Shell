#include "utils.h"

struct utsname buffer;//for user name
char pidint[100];
char input[1000],inp[100][1000],comand[100][1000];
char adir[1000],ndir[1000],odir[1000],perdir[1000],list[500][1000],faltu[1000];

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

extern v cd(char* inpp)

{
    if(rd(inpp))
    {
        for(ll i=0;i<=strlen(ndir);++i)
        {
            adir[i]=ndir[i];
        }
        chdir(adir);
    }
}

extern ll rd(char* inpp)
{
  
    if(inpp[0]=='~')
    {
        for(ll i=0;i<=strlen(adir);++i)
        {
            perdir[i]=adir[i];
        }
        for(ll i=0;i<strlen(odir);++i)
        {
            ndir[i]=odir[i];
        }
        for(ll i=strlen(odir),j=1;j<=  strlen(inpp);++i,++j)
        {
            ndir[i]=inpp[j];
        }
        return checkdir();
    }
    else if(inpp[0]=='.')
    {
        for(ll i=0;i<=strlen(adir);++i)
        {
            perdir[i]=adir[i];
        }
        if(inpp[1]=='/')
        {
            for(ll i=0;i<strlen(adir);++i)
            {
                ndir[i]=adir[i];
            }
            for(ll i=strlen(adir),j=1;j<=strlen(inpp);++i,++j)
            {
                ndir[i]=inpp[j];
            }
            return checkdir();
        }
        else if(inpp[1]=='.')
        {
            for(ll i=0;i<=strlen(adir);++i)
            {
                ndir[i]=adir[i];
            }
            ll c=0,p=0,lm;
            for(p=0;inpp[p]=='.'||inpp[p+1]=='.';++p)
            {
                if(inpp[p]=='.')
                {
                    ++c;
                }
            }
            c/=2;
            for(lm=strlen(ndir)-1;c>0&&lm>=0;--lm)
            {
                if(ndir[lm]=='/')
                {
                    --c;
                }
            }
            for(ll i=lm+1;p<=strlen(inpp);++p,++i)
            {
                ndir[i]=inpp[p];
            }
            return checkdir();
        }

    }

    else if(inpp[0]=='-'){
        //printf("uuu\n");
        // for(ll i=0;i<=strlen(perdir);++i)
        // {
        //     ndir[i]=perdir[i];

        // }
        strcpy(ndir,perdir);
        return checkdir();

    }
  
    else {
        for(ll i=0;i<=strlen(adir);++i)
        {
            perdir[i]=adir[i];
        }
        for(ll i=0;i<strlen(adir);++i)
        {
            ndir[i]=adir[i];
        }
        
        for(ll i=strlen(ndir),j=-1;j<=strlen(inpp); ++i,++j){
            if(j==-1){
                ndir[i]='/';
            }
            else{
            ndir[i]=inpp[j];
            }
            printf("%s\n",ndir);
        }
        return checkdir();
    }
    

    // else if(chdir(inpp)==-1)
    // {
    //    perror("chdir() to path failed"); 

    // }
    return ;
}

ll checkdir()
{
    
    DIR *dr = opendir(ndir);
    if (dr != NULL)
    {
        return 1;
    }
    else
    {
        perror("Error: ");
        return 0;
    }
}
