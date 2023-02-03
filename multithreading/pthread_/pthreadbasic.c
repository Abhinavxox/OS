#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>

void *myThreadFun(void *vargp)
{
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return NULL;
}

int main()
{
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id, NULL, myThreadFun, NULL);
	pthread_join(thread_id, NULL);
	printf("After Thread\n");
	exit(0);
}

/*
This is a simple program that creates a new thread using the pthread_create function and waits for it to complete using the pthread_join function.

The pthread_create function takes four arguments

A pointer to a pthread_t variable that will receive the ID of the new thread.
A pointer to a pthread_attr_t structure that specifies thread attributes. In this case, it is set to NULL, which means that default attributes will be used.
A pointer to the function that will be executed by the new thread. In this case, it is myThreadFun.
An argument to be passed to the thread function. In this case, it is NULL.
The myThreadFun function is a normal C function that takes a single void * argument and returns a void * value. It will be executed as a separate thread when its name is specified in the pthread_create function.

The pthread_join function waits for the specified thread to complete and returns its exit status. In this case, it is passed the ID of the thread that was created and a pointer to a void * variable that will receive the thread's exit status, which is set to NULL since it is not used.

The main thread of the program prints "Before Thread" and then creates the new thread using pthread_create. It then waits for the new thread to complete using pthread_join and prints "After Thread" when the thread has finished.
*/