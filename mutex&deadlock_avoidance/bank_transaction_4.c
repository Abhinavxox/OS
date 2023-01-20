#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[100];
pthread_t tid2[100];

pthread_mutex_t lock_acc_1;
pthread_mutex_t lock_acc_2;

int acc_1_bal = 20000; 	// balance in account 1
int acc_2_bal = 0;	// balance in account 2


// Transaction thread
void* transaction(void* amount)
{
	int j;
		
	pthread_mutex_lock(&lock_acc_1); 
	pthread_mutex_lock(&lock_acc_2);
	printf("\n Account 1 bal (before transfer): %d", acc_1_bal);
		
	// CRITICAL SECTION	
	if (acc_1_bal - (int) amount > 0) {
		for(j = 0; j < 0x00000FFF; j++);
		acc_1_bal = acc_1_bal - (int) amount;
		acc_2_bal = acc_2_bal + (int) amount; 	 	
	}
	

	printf("\n Amount transferred: %d", (int) amount);
	printf("\n Account 1 bal (after transfer): %d", acc_1_bal);
	printf("\n Account 2 bal: %d\n", acc_2_bal);
	
	pthread_mutex_unlock(&lock_acc_1);
	pthread_mutex_unlock(&lock_acc_2);
	
	return NULL;
}


// Check Balance thread
void* check_bal() {
	pthread_mutex_lock(&lock_acc_1); 
	pthread_mutex_lock(&lock_acc_2);
	int j;
	
	for(j = 0; j < 0x00000FFF; j++);
	printf("\n **** Account 2 bal: %d *****\n", acc_2_bal);
	pthread_mutex_unlock(&lock_acc_1);
	pthread_mutex_unlock(&lock_acc_2);
}


int main(void)
{
	int error;
	int amt_transfer = 2500;
	int i = 0;
	int num_transactions = 10;

	/* 
	* Create mutexes for the two accounts
	*/
	
	// write your code here
	pthread_mutex_init(&lock_acc_1, NULL);
	pthread_mutex_init(&lock_acc_2, NULL);
	
	/* ========================================
	*	DO NOT EDIT THE BELOW LINES
	*  ======================================== */ 
	// create 50 thread to do the transactions
	for (i=0; i < num_transactions; i++) {
	
		// thread to call transaction
		error = pthread_create(&(tid[i]), NULL, &transaction, (void*) (amt_transfer-i*100));

		if (error != 0) {
			printf("\nThread can't be created : [%s]", strerror(error));
		}
	}

	// create 50 thread to check balance
	for (i=0; i < num_transactions; i++) {
	
		// thread to call transaction
		error = pthread_create(&(tid2[i]), NULL, &check_bal, NULL);

		if (error != 0) {
			printf("\nThread can't be created : [%s]", strerror(error));
		}
	}
	
	for (i=0; i < num_transactions; i++) {
		pthread_join(tid[i], NULL);
	}
	
	for (i=0; i < num_transactions; i++) {
		pthread_join(tid2[i], NULL);
	}
	
	/* ========================================
	*	DO NOT EDIT ENDS HERE
	*  ======================================== */ 
	
	
	/* 
	* Destroy the mutexes you created
	*/
	
	// write your code here
	pthread_mutex_destroy(&lock_acc_1);
	pthread_mutex_destroy(&lock_acc_2);
	
	return 0;
}


