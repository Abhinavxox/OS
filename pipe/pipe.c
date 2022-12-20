#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    int fd[2], n;
    char buffer[100];
    pid_t p;
    pipe(fd);
    p = fork();
    if(p>0)
    {
        //if in parent
        printf("Passing value to child \n");
        write(fd[1], "hello\n", 6);
    }
    
    else
    {
        printf("Received data in child \n");
        n = read(fd[0], buffer, 100);
        write(1,buffer,n);
   }
    
}