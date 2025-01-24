#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("usage\n");
        return 1;
    }

    char* file1=argv[1];
    int status=unlink(file1);
    if (status!=0) //status ==-1
    {
        perror("cant delete");
        return 1;
    }
    return 0;
}