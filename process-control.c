#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> //for WIFEXITED

int main(int argc, char* argv[])
{
    pid_t p=fork();
    int ret_val;
    if(p<0) //p==-1
    {
        perror("fork unsuccesfful");
        return 1;
    }
    else if(p==0) //if pid is 0, we are in child
    {
        //getpid() and getppid() return type is pid_t, but it can be typecasted to int and printed out
        printf("\n in child process. \n pid of child=\t %d\n pid of parent=\t %d\n",getpid(),getppid());
        execl("./binary_search",argv[1],NULL);
    }
    else{
        
        printf("in parent process with pid %d\n",getpid());
        wait(&ret_val);
        printf("in parent process with pid %d\n",getpid());
        if(WIFEXITED(ret_val)==1)
        {
            printf("child process termianted normally \n");
        }
        else
        {
            printf("child process termianted abnormally \n");
        }

    }
}