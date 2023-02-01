#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_READERS 5

char buffer[BUFFER_SIZE];
int read_count = 0;
int write_count = 0;

pthread_t writer_thread, reader_threads[NUM_READERS];
pthread_mutex_t mutex, write_mutex;
// sem_t full, empty;

void *writer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        buffer[write_count % BUFFER_SIZE] = 'w';
        write_count++;
        printf("Writer wrote to buffer[%d]. Buffer: ", write_count % BUFFER_SIZE);
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%c ", buffer[i]);
        }
        printf("\n");
        sleep(1);
        pthread_mutex_unlock(&write_mutex);
    }
}

void *reader(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        pthread_mutex_lock(&write_mutex);
        buffer[read_count % BUFFER_SIZE] = '_';
        read_count++;
        printf("Reader %d read from buffer[%d]. Buffer: ", id, read_count % BUFFER_SIZE);

        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%c ", buffer[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(6);
    }
}

int main(int argc, char const *argv[])
{

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_mutex, NULL);
    pthread_create(&writer_thread, NULL, writer, NULL);

    for (int i = 0; i < NUM_READERS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&reader_threads[i], NULL, reader, (void *)id);
    }

    pthread_join(writer_thread, NULL);

    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(reader_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_mutex);
    return 0;
}