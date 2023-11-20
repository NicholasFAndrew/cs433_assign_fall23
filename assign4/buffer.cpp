/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief Implementation file for the buffer class
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
#include <vector>
#include <mutex>
#include <condition_variable>
using namespace std;

//Buffer class with variables initlialised to track size, count, front, and last in list
Buffer::Buffer(int size){
    buffer[0] = 0;
    this->size = size;
    this->count = 0;
    this->front = 0;
    this->last = 0;
    
}

//Destructor of Buffer, emptying before deletion
Buffer::~Buffer(){
    while(!is_empty()){
        buffer_item b = buffer[front];
        remove_item(&b);
    }
}

//inserts item into queue. If queue is empty, always inserts in the front, if an item exists, puts in last open
//spot in the queue. Increments count if added successfully
bool Buffer::insert_item(buffer_item item){
    if(!is_full()){
        if (count == 0) {
            buffer[front] = item;
        } else {
            last = (last + 1) % get_size();
            buffer[last] = item;
        }
        count++;
        return true;
    }

    return false;
}

//Removes item from the queue if there is an item that can be removed. Decrements the count if successfully removed
bool Buffer::remove_item(buffer_item *item){
    if(!is_empty()){
        *item = buffer[front];
        front = (front + 1) % get_size();
        count--;
        return true;
    }

    return false;
}

//Gets buffer size
int Buffer::get_size(){
    return size;
}

//Gets buffer count
int Buffer::get_count(){
    return count;
}

//verifies if buffer is empty
bool Buffer::is_empty(){
    return count == 0;
}

//verifies if buffer is full
bool Buffer::is_full(){
    return this->count == this->size;
}

//Prints out contents of buffer separated by ", " if needed
void Buffer::print_buffer(){
   if(is_empty()){
        cout << "[empty]" << endl;
   }else{
        int temp = front;
        cout << "Buffer [";
        for(int i = 0; i < count - 1; i++){
            cout << buffer[temp] << ", ";
            temp = (temp + 1) % buffer_size;
        }
        cout << buffer[last] << "]" << endl;
   }
}
