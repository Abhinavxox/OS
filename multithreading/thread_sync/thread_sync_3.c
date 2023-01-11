#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];

int counter; 
// 1. Initialize/assign this variable to the last four-digits of your roll number
counter = 88;


// Thread 1 to do JOB 1
void* thread_1(void* arg)
{
	
	// 2.1 Write the code to modify the counter variable by increasing it by 1
	counter = counter + 1;
	// 2.2 Print the counter variable
	printf("\nThe counter is %d\n", counter);

	return NULL;
}

// Thread 2 to do JOB 2
void* thread_2(void* arg)
{
	
	// 3.1 Write the code to modify the counter variable by decreasing it by 2
	counter = counter - 2;
	// 3.2 Print the counter variable
	printf("\nThe counter is %d\n", counter);

	return NULL;
}

int main(void)
{
	int error;


	// 4. modify the below line to create the first thread, that does JOB 1 using thread 1
	error = pthread_create(&(tid[0]), NULL, thread_1, NULL);
	if (error != 0) {
		printf("\nThread can't be created : [%s]", strerror(error));
	}
	
	// 5. create the second thread to the JOB 2 using thread 2 (you may copy re-use the above few lines of code)
	error = pthread_create(&(tid[1]), NULL, thread_2, NULL);
	if (error != 0) {
		printf("\nThread can't be created : [%s]", strerror(error));
	}
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	
	return 0;
}