#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

// Define a semaphore structure to maintain each fork's state
struct semaphore {
    int mutex_value;        // 1 if available, 0 if not
    pthread_t* waiting_list; // List of threads waiting for the fork
};

// Declare semaphores for each fork
struct semaphore forks[N];

// Declare the philosophers' threads
pthread_t philosophers[N];

// Function declarations
void* philosopher(void* arg);
void think(int id);
void eat(int id);
void take_forks(int id);
void put_forks(int id);
void wait(struct semaphore* s);
void signal(struct semaphore* s);

int main() {
    // Initialize semaphores for each fork
    for (int i = 0; i < N; i++) {
        forks[i].mutex_value = 1; // All forks are initially available
        forks[i].waiting_list = NULL; // No one is waiting initially
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void*)(long)i);
    }

    // Join philosopher threads (they run forever in this case)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void* philosopher(void* arg) {
    int id = (int)(long)arg;
    while (1) {
        think(id);
        take_forks(id);
        eat(id);
        put_forks(id);
    }
}

void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    sleep(1);  // Thinking for some time
}

void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(2);  // Eating for some time
}

void take_forks(int id) {
    // Wait for the left fork
    wait(&forks[id]);

    // Wait for the right fork (next fork in circular manner)
    wait(&forks[(id + 1) % N]);

    printf("Philosopher %d took both forks.\n", id);
}

void put_forks(int id) {
    // Release the left fork
    signal(&forks[id]);

    // Release the right fork (next fork in circular manner)
    signal(&forks[(id + 1) % N]);

    printf("Philosopher %d put down both forks.\n", id);
}

void wait(struct semaphore* s) {
    // If the semaphore is not available, block the philosopher and wait
    while (s->mutex_value <= 0) ;
    s->mutex_value = 0;  // Fork is now taken by the philosopher
}

void signal(struct semaphore* s) {
    s->mutex_value = 1;  // Fork is now available
}
