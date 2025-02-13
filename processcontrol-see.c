#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
int main(int argc,char* argv[1])
{
    pid_t pid=fork();
    int status;
    if (pid==-1)
    {
        perror("fork error");
    }
    else if(pid==0)
    {
        printf("We are in child process now.\n Child pid:\t %d \nParent pid:\t %d \n",getpid(),getppid());
        execl("./binarysearch-see",argv[1],NULL);
    }
    else
    {
        printf("We are in parent process now.\nParent pid:\t%d\n",getpid());
        wait(&status);
        if((WIFEXITED(status))==0)
        {
            printf("terminated abnormally\n");
        }
        else
        {
            printf("terminated normally\n");
        }

    }
    return 0;

}
