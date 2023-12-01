#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int buffer[5];
int count = 0;

void *producer(void *arg) {
    long int num = (long int)arg;

    pthread_mutex_lock(&mutex);

    // Check if there's space in the buffer
    if (count < 5) {
        // producer is producing a data
        buffer[count] = rand() % 10;
        printf("Producer %ld produced: %d\n", num + 1, buffer[count]);
        count++;
      //  sleep(1);
    } else {
        printf("Buffer is full, producer %ld cannot produce.\n", num + 1);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    long int num = (long int)arg;

    pthread_mutex_lock(&mutex);

    // Check if there's data to consume
    if (count > 0) {
        // consumer is consuming a data
        count--;
        printf("Consumer %ld consumed: %d\n", num + 1, buffer[count]);
       // sleep(1);
    } else {
        printf("Buffer is empty, consumer %ld cannot consume.\n", num + 1);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    int np, nc;
    pthread_t p[10], c[10]; 
    unsigned long int i, j, k, l;

    printf("Enter the number of producers and consumers: ");
    scanf("%d %d", &np, &nc);

    // declaration of mutex
    pthread_mutex_init(&mutex, NULL);

    // create producer threads
    for (i = 0; i < np; i++) {
        pthread_create(&p[i], NULL, producer, (void *)i);
    }

    // create consumer threads
    for (j = 0; j < nc; j++) {
        pthread_create(&c[j], NULL, consumer, (void *)j);
    }

    // join producer threads
    for (k = 0; k < np; k++) {
        pthread_join(p[k], NULL);
    }

    // join consumer threads
    for (l = 0; l < nc; l++) {
        pthread_join(c[l], NULL);
    }

    // destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

