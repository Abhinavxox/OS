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
	// int j;
	int amt = *((int*)amount);
	printf("\n Account 1 bal (before transfer): %d", acc_1_bal);
		
	// CRITICAL SECTION	
	if (acc_1_bal - (int) amount > 0) {
		//for(j = 0; j < 0x00000FFF; j++); // simply spin - to see the effect of race condition
		acc_1_bal = acc_1_bal - (int) amount;
		acc_2_bal = acc_2_bal + (int) amount; 	 	
	}
	

	printf("\n Amount transferred: %d", (int) amount);
	printf("\n Account 1 bal (after transfer): %d", acc_1_bal);
	printf("\n Account 2 bal: %d\n", acc_2_bal);
	// END OF CRITICAL SECTION
	return NULL;
}

// Check Balance thread
void* check_bal() {

	// int j;
	//for(j = 0; j < 0x00000FFF; j++); // simply spin - to see the effect of race condition
	printf("\n **** Account 2 bal: %d *****\n", acc_2_bal);
}


int main(void)
{
	int error;
	int amt_transfer = 2500;
	int i = 0;
	int num_transactions = 10;

	// initialize mutex

	//create threads to do the transactions
	for (i=0; i < num_transactions; i++) {
		error = pthread_create(&(tid[i]), NULL, &transaction, (void*) (amt_transfer)); // thread to do the transaction

		if (error != 0) {
			printf("\nThread can't be created : [%s]", strerror(error));
		}
	}

	// create threads to check balance
	for (i=0; i < num_transactions; i++) {
		error = pthread_create(&(tid2[i]), NULL, &check_bal, NULL); // thread to check balance

		if (error != 0) {
			printf("\nThread can't be created : [%s]", strerror(error));
		}
	}
	
	// Parent process wait till all the threads complete execution
	for (i=0; i < num_transactions; i++) {
		pthread_join(tid[i], NULL);
		pthread_join(tid2[i], NULL);
	}

	return 0;
}

