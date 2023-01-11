#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// global variable
int g = 0;

void *myThreadFun(void *vargp)
{
	// storing the argument
	int *myid = (int *)vargp;

	//static variable to observe its changes
	static int s = 0;

	++s; ++g;

	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

int main()
{
	int i;
	pthread_t tid;

	// 3 threads
	for (i = 0; i < 5; i++)
		pthread_create(&tid, NULL, myThreadFun, (void *)&tid);

	pthread_exit(NULL);
	return 0;
}
