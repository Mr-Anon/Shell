#include "utils.h"

struct utsname buffer;
char input[1000],inp[100][1000],comand[100][1000];
char adir[1000],ndir[1000],odir[1000],list[500][1000],faltu[1000];
char pidint[100];

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

extern v ls(ll comc)
{
    if(comc==1)//ls
    {
        DIR *dr = opendir(adir);
        if (dr == NULL)  // opendir returns NULL if couldn't open directory
        {
            perror("Error: ");
            return;
        }
        else
        {
        struct dirent *de;
            while ((de = readdir(dr)) != NULL)
            {
                if((de->d_name)[0]!='.')
                {
                    printf("%s\n", de->d_name);
                }
            }
        }
    }

    else if(comand[1][0]=='-')
    {
        if(strcmp(comand[1],"-a")==0)//ls -a
        {
            DIR *dr = opendir(adir);
            if (dr == NULL)  // opendir returns NULL if couldn't open directory
            {
                perror("Error: ");
                return;
            }
            else
            {
            struct dirent *de;
                while ((de = readdir(dr)) != NULL)
                {
                    printf("%s\n", de->d_name);
                }
            }

        }
        else
        {
            DIR *dr = opendir(adir);
            if (dr == NULL)  // opendir returns NULL if couldn't open directory
            {
                perror("Error: ");
                return;
            }
            else
            {
            struct dirent *de;
                ll filecount=0;
                while ((de = readdir(dr)) != NULL)
                {
                    strcpy(list[filecount],de->d_name);
                    ++filecount;
                }
                char path[1000];
                for(ll i=0;i<filecount;++i)
                {
                    strcpy(path,adir);
                    strcat(path,"/");
                    strcat(path,list[i]);
                    if(strcmp(comand[1],"-l")==0)
                    {
                        if(!(list[i][0]=='.'))
                        {
                            printinfo(path,list[i]);

                        }
                    }
                    else
                    {
                        printinfo(path,list[i]);
                    }
                }

            }
        }
    }

    else if(comc==2)// ls<dirname>
    {
        if(rd(comand[1]))
        {
            DIR *dr = opendir(ndir);
            if (dr == NULL)  // opendir returns NULL if couldn't open directory
            {
                perror("Error: ");
                return;
            }
            else
            {
            struct dirent *de;
                while ((de = readdir(dr)) != NULL)
                {
                    if((de->d_name)[0]!='.')
                    {
                        printf("%s\n", de->d_name);
                    }
                }
            }
        }
    }
}

v printinfo(char* path,char* list)
{
    struct stat buf;
    stat(path, &buf);
    if (S_ISREG(buf.st_mode))
    {
        printf("-");
    }
    else if (S_ISDIR(buf.st_mode))
    {
        printf("d");
    }

    if (buf.st_mode & S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IROTH )
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWOTH )
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    
    printf("  %d %d %d", buf.st_nlink,buf.st_uid,buf.st_gid);
    printf("%13d ", buf.st_size);
    printf("%s %s\n", ctime(&(buf.st_mtime))+4,list);
}