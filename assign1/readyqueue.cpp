#include <iostream>
#include "readyqueue.h"
#include "pcbtable.h"
#include "pcb.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class. has a count of current number of values
 * 
 */
ReadyQueue::ReadyQueue()  {
    capacity = 500;
    heaparray = new PCB[capacity];
    count = 0;
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] heaparray;
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    // When adding a PCB to the queue, you must change its state to READY.
    if (count == capacity) {
        PCB* newArray = new PCB[capacity*2];
        heaparray = newArray;
        capacity = capacity*2;
    }
    pcbPtr->setState(ProcState::READY);
    heaparray[count] = *pcbPtr;
    count++;
    percolateUp(count-1);
    //std::cout << "This is the count: " << count << endl;

}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    // When removing a PCB from the queue, you must change its state to RUNNING.
    PCB* retval = new PCB;
    heaparray[0].setState(ProcState::RUNNING);
    *retval = heaparray[0];
    //std::cout << "This is what return value should be: " << heaparray[0].getPriority() << endl;
    heaparray[0] = heaparray[count-1];
    //std::cout << "This is what was put on top: " << heaparray[count-1].getPriority() << endl;
    heaparray[count-1].~PCB();
    count--;
    percolateDown(0);
    //std::cout << "This is what the return value is: " << retval->getPriority() << endl;
    return retval;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < count; i++){
        heaparray[i].display();
    }
}

void ReadyQueue::percolateDown(int index) {
    // Run recursively until the current node is bigger than its children
    while(heaparray[index].getPriority() < heaparray[leftChild(index)].getPriority() || heaparray[index].getPriority() < heaparray[rightChild(index)].getPriority()){
        if(heaparray[leftChild(index)].getPriority() < heaparray[rightChild(index)].getPriority()){
            swap(index,rightChild(index));
            index = rightChild(index);
        } else {
            swap(index,leftChild(index));
            index = leftChild(index);
        }
    }
}

void ReadyQueue::swap(int index1, int index2) {
    //std::cout << "Swap " << heaparray[index1].getPriority() << " with " << heaparray[index2].getPriority() << endl;
    std::swap(heaparray[index1],heaparray[index2]);
    //std::cout << "Now it is " << heaparray[index1].getPriority() << " and " << heaparray[index2].getPriority() << endl;
}

void ReadyQueue::percolateUp( int index) {
    // run recursively until the current node is small than its parent
    while(heaparray[index].getPriority() > heaparray[parent(index)].getPriority()){
        swap(index,parent(index));
        index = parent(index);
    }
}

ReadyQueue::ReadyQueue(const ReadyQueue& heap) {
    capacity = heap.capacity;
    for (int i = 1; i <= heap.count; i++)
    {
        heaparray[i - 1] = heap.heaparray[i - 1];
    }
    count = heap.count;
}

/**
  * @brief assignment operator to set one heap to another
  * @param the heap that you want to set your heap to
  */
ReadyQueue& ReadyQueue::operator = (const ReadyQueue& heap)
{
    if (this != &heap)
    {
        capacity = heap.capacity;
        for (int i = 1; i <= heap.count; i++)
        {
            heaparray[i - 1] = heap.heaparray[i - 1];
        }
        count = heap.count;
    }
    return *this;
}
