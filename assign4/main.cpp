/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <random>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include "buffer.h"
#include <unistd.h>


using namespace std;

// global buffer object
Buffer buffer;
pthread_mutex_t mtx;
sem_t full;
sem_t nothing;
pthread_attr_t att;
// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        pthread_mutex_unlock (&mtx);
        sem_post(&full);
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        sem_wait(&full);
        pthread_mutex_lock (&mtx);

        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&mtx);
        sem_post(&nothing);
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
    if(argc != 4){
        cout << "Invalid number of arguemnts, correct usage is as follows: " << endl;
        cout << "./assign4 <sleeptime> <pthreadc> <cthreadc>" << endl;
        exit(1);
    }

    int sleepTime = atoi(argv[1]);
    int pThreadc = atoi(argv[2]);
    int cThreadc = atoi(argv[3]);

    pthread_t pThreads;
    pthread_t cThreads;

    pthread_mutex_init (&mtx, nullptr);
    sem_init(&nothing,0, buffer_size);
    sem_init(&full,0,0);

    for(int i = 0; i < pThreadc; i++){
        int *arg = new int;

        if(arg == nullptr){
            cout << "Can't allocate memory" << endl;
            exit(0);
        }

        *arg = i + 1;

        pthread_create(&pThreads, &att, producer,(void*) arg);
    }

    for(int i = 0; i < cThreadc; i++){
        pthread_create(&cThreads, &att, consumer, nullptr);
    }

    sleep(sleepTime);

    cout << endl << "Threads Done. Exiting..." << endl;
    exit(0);

}
