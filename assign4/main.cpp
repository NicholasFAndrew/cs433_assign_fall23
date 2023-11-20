/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;

// global buffer object
Buffer buffer;
pthread_mutex_t mtx;
sem_t full;
sem_t nothing;
pthread_attr_t att;

// Producer thread function
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        //Waits for semaphore to show open spots
        sem_wait(&nothing);
        //takes the mutex lock
        pthread_mutex_lock (&mtx);

        //inserts an item if there is one to insert
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        //releases the mutex lock
        pthread_mutex_unlock (&mtx);
        //increases the full count of the semaphore
        sem_post(&full);
    }
}

// Consumer thread function
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        //waits for the full semaphore to have an available item
        sem_wait(&full);
        //takes control of the mutex lock
        pthread_mutex_lock (&mtx);

        //If there is an item to remove, it will remove it
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        //unlocks the mutex lock
        pthread_mutex_unlock(&mtx);
        //increments the 'nothing' semaphore to show an open space
        sem_post(&nothing);
    }
}

int main(int argc, char *argv[]) {

    //checks to see if the input has the appropriate number of arguements
    if(argc != 4){
        cout << "Invalid number of arguemnts, correct usage is as follows: " << endl;
        cout << "./assign4 <sleeptime> <pthreadc> <cthreadc>" << endl;
        exit(1);
    }

    //initializes the inputted arguements to the appropriate variables
    int sleepTime = atoi(argv[1]);
    int pThreadc = atoi(argv[2]);
    int cThreadc = atoi(argv[3]);

    pthread_t pThreads;
    pthread_t cThreads;

    //initializes the mutex lock
    pthread_mutex_init (&mtx, nullptr);
    //initializes the nothing semaphore
    sem_init(&nothing,0, buffer_size);
    //initializes the full semaphore
    sem_init(&full,0,0);

    //makes a new producer thread according to the given argument
    for(int i = 0; i < pThreadc; i++){
        int *arg = new int;
        if(arg == nullptr){
            cout << "Can't allocate memory" << endl;
            exit(0);
        }
        *arg = i + 1;
        pthread_create(&pThreads, &att, producer,(void*) arg);
    }

    //makes a new consumer thread according to the given arguement
    for(int i = 0; i < cThreadc; i++){
        pthread_create(&cThreads, &att, consumer, nullptr);
    }

    //Main thread waits according to the given arguement
    sleep(sleepTime);

    //calls our finished waiting time and exits the program
    cout << endl << "Threads Done. Exiting..." << endl;
    exit(0);

}
