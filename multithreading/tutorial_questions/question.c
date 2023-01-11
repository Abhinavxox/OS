#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int x = 0; 
sem_t s; 

// T1
void* processT1(void* arg)
{
sem_wait(&s); 
int i = x;
sleep(1);
i++; 
x=i;
sem_post(&s); 
return NULL;
}

// T2
void* processT2(void* arg)
{
sleep(1);
sem_wait(&s); 
x++; 
sem_post(&s); 
return NULL;
}

// T3
void* processT3(void* arg)
{
sem_wait(&s); 
x = x-2; 
sem_post(&s); 
return NULL;
}

// T4
void* processT4(void* arg)
{
sem_wait(&s); 
x = x-2; 
sem_post(&s); 
return NULL;
}

int main()
{
sem_init(&s, 0, 2);
pthread_t t1,t2,t3,t4;
pthread_create(&t1, NULL, processT1, NULL);
pthread_create(&t2, NULL, processT2, NULL);
pthread_create(&t3, NULL, processT3, NULL);
pthread_create(&t4, NULL, processT4, NULL);

// wait for threads to complete
pthread_join(t1, NULL);
pthread_join(t2, NULL);
pthread_join(t3, NULL);
pthread_join(t4, NULL);

printf("x = %d\n", x); 
return 0;
}