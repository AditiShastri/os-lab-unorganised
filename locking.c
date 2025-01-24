
//file access

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 100

int main(int argc, char* argv[])
{
    if (argc!=2)
    {
        printf("usage: %s filename\n",argv[0]);
        return -1;
    }
    int fd=open(argv[1],O_RDWR); //open is in fcntl
    if(fd==-1)
    {
        perror("open");
        return -1;
    }

    struct flock fvar;

    //now we initialise the lock, these characteristics will be imbibed by the fvntl funciton
    fvar.l_type=F_WRLCK;
    fvar.l_whence=SEEK_END;
    fvar.l_len=100;
    fvar.l_start=SEEK_END-100;

    //ask user to lock
    printf("press enter to lock\n");
    getchar();

  
    if ((fcntl(fd,F_SETLK,&fvar))==-1)
    {
        fcntl(fd,F_GETLK,&fvar);
        printf("file is locked by process with pid %d",fvar.l_pid);
        return -1;
    }

    printf("file lcoked succesfully\n");
    
    if((lseek(fd,-100,SEEK_END))==-1)
    {
        perror("seek error\n");
        return -1;
    }

    char buf[SIZE];

    if((read(fd,buf,SIZE))==-1)
    {
        perror("read error");
        return -1;
    }

    printf("data read from file\n");
    puts(buf);

    printf("press enter to unlock");
    getchar();

    fvar.l_type=F_UNLCK;
    fvar.l_whence=SEEK_SET;
    fvar.l_len=0;
    fvar.l_start=0;

    if((fcntl(fd,F_UNLCK,&fvar))==-1)
    {
        perror("unlock error");
        return -1;
    }

    printf("unlocked\n");



    

    close(fd);
    
    return 0;
}