//create a variable x and put in two threads 
//one thread calculates the sum from 1 to x
//other tread calculates the factorial of x

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;
int sum = 0;
int factorial = 1;

void *sumThread(void *vargp)
{
    int i;
    for (i = 1; i <= x; i++)
    {
        sum += i;
    }
    printf("Sum of numbers from 1 to %d is %d\n", x, sum);
}

void *factorialThread(void *vargp)
{
    int i;
    for (i = 1; i <= x; i++)
    {
        factorial *= i;
    }
    printf("Factorial of %d is %d\n", x, factorial);
}

int main()
{
    pthread_t sumThread_id;
    pthread_t factorialThread_id;
    printf("Enter a number: ");
    scanf("%d", &x);
    pthread_create(&sumThread_id, NULL, sumThread, NULL);
    pthread_create(&factorialThread_id, NULL, factorialThread, NULL);
    pthread_join(sumThread_id, NULL);
    pthread_join(factorialThread_id, NULL);
    exit(0);
}