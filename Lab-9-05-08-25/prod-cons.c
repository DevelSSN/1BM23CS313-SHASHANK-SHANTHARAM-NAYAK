#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
int full = 0;
int empty = N;
int mutex = 1;
int BUFFER[N];
int in = 0; // Index for producing
int out = 0; // Index for consuming

void wait(int* s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int* s) {
    (*s)++;
}

void produce(int item) {
    wait(&empty);
    wait(&mutex);
    BUFFER[in] = item;
    in = (in + 1) % N;
    printf("Produced: %d\n", item);
    signal(&mutex);
    signal(&full);
}

void consume() {
    wait(&full);
    wait(&mutex);
    int item = BUFFER[out];
    out = (out + 1) % N;
    printf("Consumed: %d\n", item);
    signal(&mutex);
    signal(&empty);
}

void* produce_thread(void* arg) {
    int item = 1;
    while (1) {
        produce(item);
        item++;
        sleep(1);
    }
    return NULL;
}

void* consume_thread(void* arg) {
    while (1) {
        consume();
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t producer, consumer;

    pthread_create(&producer, NULL, produce_thread, NULL);
    pthread_create(&consumer, NULL, consume_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}
