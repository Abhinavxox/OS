#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void fork3()
{
    int ret;
    ret = fork();
    if (ret == 0)
        printf("\n [%id] Hello from child\n",getpid());
    else
        printf("\n [%id] Hello from parent\n",getpid());
}

int main ()
{
    fork3();
    return 0;
}