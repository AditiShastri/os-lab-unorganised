//cp a b
//we use file system calls close(),read(),write()- found in unistd
//open()- fcntl.h

#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 8192
#include <fcntl.h> //for open()
#include <sys/types.h>

int main(int argc, char* argv[])
{

    if(argc!=3)
    {
        perror("usage");
    }

    int fd1=open(argv[1],O_RDONLY);
    if(fd1==-1)
    {
        perror("cant open");
        return -1;
    }
    int fd2=open(argv[2],O_WRONLY | O_CREAT, 0644);
    if(fd2==-1)
    {
        perror("cant open");
        return -1;
    }

    ssize_t ret_in,ret_out;
    char buf[BUF_SIZE];

    while((ret_in=read(fd1,&buf,BUF_SIZE))!=0)
    {
        ret_out=write(fd2,&buf,(ssize_t) ret_in);
        if (ret_out==-1)
        {
            perror("cant write");
            return -1;
        }
    }
    

    close(fd1);
    close(fd2);












    return 0;
}