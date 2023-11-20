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
    buffer[0] = 0;
    this->size = size;
    this->count = 0;
    this->front = 0;
    this->last = 0;
    
}

Buffer::~Buffer(){
    while(!is_empty()){
        buffer_item b = buffer[front];
        remove_item(&b);
    }
}


bool Buffer::insert_item(buffer_item item){
    if(!is_full()){
        last = (last + 1) % get_size();
        count++;
        return true;
    }

    return false;
}

bool Buffer::remove_item(buffer_item *item){
    if(!is_empty()){
        *item = buffer[front];
        front = (front + 1) % get_size();

        return true;
    }

    return false;
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
   if(is_empty()){
        cout << "[empty]" << endl;
   }else{
        int temp = front;
        cout << "Buffer [";
        for(int i = 0; i < count; i++){
            cout << buffer[temp] << " ";
            temp = (temp + 1) % buffer_size;
        }
        cout << "]" << endl;
   }
}
