#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main()
{
    char P[10]="rwxrwxrwx";
    char AP[10]="";
    DIR* d =opendir(".");
    readdir(d);
    readdir(d);

    struct dirent * de;
    struct stat buf;

    while((de=readdir(d))!=NULL) //de is of type struct dirent *, so it is a pointer. while the next directory entry is not null,
    {
        stat(de->d_name,&buf);
        
        if(S_ISDIR(buf.st_mode))
        {
            printf("d");
        }
        if(S_ISFIFO(buf.st_mode))
        {
            printf("p");
        }
        if(S_ISSOCK(buf.st_mode))
        {
            printf("s");
        }
        if(S_ISBLK(buf.st_mode))
        {
            printf("b");
        }
        if(S_ISCHR(buf.st_mode))
        {
            printf("c");
        }
        if(S_ISREG(buf.st_mode))
        {
            printf("-");
        }
       
        int i,j;
        for(i=0,j=1<<8;i<9;i++,j=j>>1)
        {
            AP[i]=(buf.st_mode & j)?P[i]:'-';
        }

        printf("%s ",AP);

        printf("%5d ",buf.st_nlink);

        struct passwd* p; //longer form of pwd
        p=getpwuid(buf.st_uid);
        printf("%.8s ",p->pw_name);

        struct group* g;
        g=getgrgid(buf.st_gid);
        printf("%-8.8s ",g->gr_name);

        printf("%8d",buf.st_size);


       

        struct tm* t;
        char time_string[26];
        t=localtime(&buf.st_mtime);
        strftime(time_string,sizeof(time_string),"%b %d %H:%M",t);
        printf(" %s ",time_string);

         printf("%s\n",de->d_name);



    }





    return 0;
}