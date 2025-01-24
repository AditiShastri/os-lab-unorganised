#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("usage\n");
        return 1;
    }

    int fd1=open(argv[1],O_RDONLY);
    if(fd1==-1)
    {
        perror("cant open file");
        return 2;
    }

    int fd2=open(argv[2],O_WRONLY | O_CREAT, 0644);
    if(fd2==-1)
    {
        perror("cant open file");
        return 2;
    }

    ssize_t ret_in,ret_out;
    char buf[BUF_SIZE];

    //  no of bytes read= read(file descriptor(which is an int), kidhar se(buffer ka address), buffer size- chunks of how much to be read)
    while((ret_in=read(fd1,&buf,BUF_SIZE))>0) //ret_in is the number of bytes read
    {
        ret_out=write(fd2,&buf,(ssize_t) ret_in); //no. of bytes written =write( fd2-where to write, from where (buffer ka address), HOW MANY (ret_in number of bytes read))
        if(ret_out==-1)
        {
            perror("Write");
            return 3;
        }
    }

    close(fd1);
    close(fd2);
    return 0;

}