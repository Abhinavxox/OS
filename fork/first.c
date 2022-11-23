#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
    int id, ret;
    ret = fork();
    id = getpid();
    printf("\n My identifier is ID = [%d]\n",id);
}