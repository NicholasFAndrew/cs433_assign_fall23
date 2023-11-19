/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author ??? (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
// TODO: Add your implementation of the buffer class here

Buffer::Buffer(int size){
    this->size = size;
    this->count = 0;
    this->in = 0;
    this->out = 0;
    buffer.resize(size);
}

Buffer::~Buffer(){
    while(!is_empty()){
        buffer_item b = buffer[buffer.front()];
        remove_item(&b);
    }
}


bool Buffer::insert_item(buffer_item item){
    unique_lock<mutex> lock(mtx);
    while(is_full()){
        notFull.wait(lock);
    }

    buffer[in] = item;
    in = (in + 1) % size;
    count++;

    notEmpty.notify_all();

    return true; 
}

bool Buffer::remove_item(buffer_item *item){
    unique_lock<mutex> lock(mtx);

    while(is_empty()){
        notEmpty.wait(lock);
    }

    *item = buffer[out];
    out = (out + 1) % size;
    count--;

    notFull.notify_all();
    return true;
}

int Buffer::get_size(){
    return size;
}

int Buffer::get_count(){
    return count;
}

bool Buffer::is_empty(){
    return count = 0;
}

bool Buffer::is_full(){
    return this->count == this->size;
}

void Buffer::print_buffer(){
    unique_lock <mutex> lock(mtx);

    cout << "Buffer: [";
    for(int i = 0 ; i < count; i++){
        cout << buffer[(out + i) % size];
        if(i < count - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;
}
