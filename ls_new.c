#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>


int main()
    {char P[10]="rwxrwxrwx";
    char AP[10]="";

    DIR *d=opendir(".");
    readdir(d);
    readdir(d);

    struct dirent* de;
    struct stat buf;

    struct passwd *p;
    struct group *g;

    struct tm *t;
    char time[26];

    int i,j;

    while((de=readdir(d))!=NULL)
    {
        stat(de->d_name,&buf);

        if(S_ISDIR(buf.st_mode))
        {
            printf("d");
        }
        if(S_ISREG(buf.st_mode))
        {
            printf("-");
        }
        if(S_ISFIFO(buf.st_mode))
        {
            printf("p");
        }
        if(S_ISSOCK(buf.st_mode))
        {
            printf("s");
        }
        if(S_ISLNK(buf.st_mode))
        {
            printf("l");
        }
        if(S_ISBLK(buf.st_mode))
        {
            printf("b");
        }
        if(S_ISCHR(buf.st_mode))
        {
            printf("c");
        }

        for(i=0,j=(1<<8);i<9;i++,j=j>>1)
        {
            AP[i]=(buf.st_mode & j)?P[i]:'-';
        }
        printf("%s",AP);

        printf("%5d ",buf.st_nlink);

        p=getpwuid(buf.st_uid);
        printf("%.8s ",p->pw_name);

        g=getgrgid(buf.st_gid);
        printf("%-8.8s",g->gr_name);

        printf("%8d ",buf.st_size);

        //time
        t=localtime(&buf.st_mtime);
        //strftime-- converts struct tm object to string
        //strftime(char * time, size of (char * time), fomrat string,struct tm* time object)
        strftime(time,sizeof(time),"%b %d %H:%M",t);
        printf("%s ",time);

        printf("%s\n",de->d_name);








    }

}