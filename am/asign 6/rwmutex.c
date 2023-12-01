#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_resource = 0;
int reader_count = 0;

pthread_mutex_t mutex; // Mutex for mutual exclusion

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        // Reader entry section
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) {
            // First reader blocks writers
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex); // Release the mutex after incrementing reader_count
        }

        // Reading the shared resource
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);

        // Reader exit section
        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            // Last reader unblocks writers
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_unlock(&mutex); // Release the mutex after decrementing reader_count

        sleep(1); // Simulate reading
    }
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        // Writer wants to write
        pthread_mutex_lock(&mutex);

        // Writing to the shared resource
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);

        // Writer done writing
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulate writing
    }
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    pthread_mutex_init(&mutex, NULL);

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

    return 0;
}

