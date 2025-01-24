#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    //educate users about usage
    if(argc!=2)
    {
        printf("USage: %s filename",argv[0]); 
        return -1;
    }

    //crux of this- the file lock
    struct flock file_lock;

    //let us open the file we want to lock
    int fd=open(argv[1],O_RDWR);

     //We create a write lock-() no body else can write AND READ ALSO on this file) - thus it prevents concurrent access really
     //on the last 100 bytes of the file

    file_lock.l_type=F_WRLCK;
    file_lock.l_whence=SEEK_END;
    file_lock.l_start=SEEK_END-100;
    file_lock.l_len=100;

    printf("Click enter to lock");
    getchar();

    if((fcntl(fd,F_SETLK,&file_lock))==-1) //lock unsuccessful
    {
        //modify file_lock to reflect the pid that owns the lock
        fcntl(fd,F_GETLK,&file_lock);
        printf("Cannot lock. File currently locked by process with pid %d",file_lock.l_pid);
        return -1;
    }

    //now the file is locked.

    printf("Locked contents:\n");

    lseek(fd,-100,SEEK_END);
    char buf[101];
    if((read(fd,&buf,100))==-1)
    {
        perror("cant read");
        return -1;
    }
    printf("%s",buf);

    printf("Press enter to unlock the file\n");
    getchar();

    file_lock.l_type=F_UNLCK;
    file_lock.l_whence=SEEK_SET;
    file_lock.l_start=0;
    file_lock.l_len=0;

    if((fcntl(fd,F_SETLK,&file_lock))==-1)
    {
        printf("could not unlock");
        return -1;
    }
    printf("Unlocked.");
    return -1;
   
    

}