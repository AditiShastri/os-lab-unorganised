#include <stdio.h>
//#include <file.h> no file.h!!!
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    //int j;
    DIR *d=opendir(".");
    readdir(d);
    readdir(d);
    struct dirent* de;
    struct stat buf;
    char P[10]="rwxrwxrwx";
    char AP[10]="";

    while((de=readdir(d)))
    {
        stat(de->d_name,&buf);
        if(S_ISREG(buf.st_mode))
        {
            printf("r");
        }
        if(S_ISFIFO(buf.st_mode))
        {
            printf("p");
        }
        if(S_ISBLK(buf.st_mode))
        {
            printf("b");
        }
        if(S_ISCHR(buf.st_mode))
        {
            printf("c");
        }
        if(S_ISSOCK(buf.st_mode))
        {
            printf("s");
        }
        if(S_ISLNK(buf.st_mode))
        {
            printf("l");
        }
        for(int i=0,j=1<<8;i<9;i++,j=j>>1)
        {
            AP[i]=(buf.st_mode && j)?P[i]:'-';
        }
        printf("%s",AP);

        printf("%5d",buf.st_nlink);

        struct passwd* p=getpwuid(buf.st_uid);
        printf("%8s",p->pw_name);

        struct group* g=getgrgid(buf.st_gid);
        printf("%-8.8s",g->gr_name);

        printf("%8d",buf.st_size);

        struct tm *t=localtime(&buf.st_mtime);
        char time[26]="";
        strftime(time,sizeof(time),"%b %d %H:%M",t);
        printf("%s ",time);

        printf("%s\n",de->d_name);

        
    }
    return 0;
}