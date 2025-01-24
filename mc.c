//mv uses the rename function present in stdio.h

#include <stdio.h>


int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("usage\n");
        return 1;
    }

    char* file1=argv[1];
    char* file2=argv[2];

    int status=rename(file1,file2);
    if (status!=0)
    {
        perror("cant rename");
        return 1;
    }
    return 0;





}
