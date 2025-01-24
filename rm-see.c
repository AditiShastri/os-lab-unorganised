#include <stdio.h>
#include <unistd.h>


int main(int argc,char* argv[])
{

    if(argc!=2)
    {
        perror("usage");
        return -1;
    }

    if((unlink(argv[1]))==-1)
    {
        perror("unlink error");
    }


    return 0;
}