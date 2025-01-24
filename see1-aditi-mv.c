//crux- use rename() function, present in stdio --check via man 2 rename
#include <stdio.h>

int main(int argc, char* argv[])
{

    //usage

    if((rename(argv[1],argv[2]))==-1)
    {
        perror("aagilla bro sorry");
        return  -1;
    }
    return 0;
}