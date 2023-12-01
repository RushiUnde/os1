#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_resource = 0;
int reader_count = 0;

pthread_mutex_t mutex; 
sem_t resource_access; 
sem_t reader_count_mutex; 

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        sem_wait(&reader_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&resource_access);
        }
        sem_post(&reader_count_mutex);

        // Reading the shared resource
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);

        sem_wait(&reader_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource_access);
        }
        sem_post(&reader_count_mutex);

        sleep(1); // Simulate reading
    }
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        sem_wait(&resource_access);   //down db

        // Writing to the shared resource
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);

        sem_post(&resource_access);

        sleep(2); // Simulate writing
    }
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&resource_access, 0, 1); // Initialize semaphore
    sem_init(&reader_count_mutex, 0, 1); // Initialize semaphore

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&resource_access);
    sem_destroy(&reader_count_mutex);

    return 0;
}

