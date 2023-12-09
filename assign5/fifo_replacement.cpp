/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

// Constructor
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) , fifo_queue() {

}

// Destructor
FIFOReplacement::~FIFOReplacement() {
    // Clear the FIFO queue during destruction
    while(!fifo_queue.empty()){
        fifo_queue.pop_back();
    }
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // Increment page fault count
    page_fault++;
    
    // Update page table entry for the new page
    page_table[page_num].valid = true;
    
    // Add the page to the back of the FIFO queue
    fifo_queue.push_back(page_num);
    
    // Update frame number in the page table
    page_table[page_num].frame_num = frame_count;
    
    // Increment the frame count
    frame_count++;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // Increment replaced page and page fault counts
    page_fault++;
    replaced_page++;
    
    // Get the index of the page at the front of the FIFO queue
    int front_index = fifo_queue.front();
    
    // Update page table entry for the victim page
    page_table[front_index].valid = false;
    
    // Remove the victim page from the FIFO queue
    fifo_queue.erase(fifo_queue.begin());
    
    // Update page table entry for the new page
    page_table[page_num].valid = true;
    
    // Add the new page to the back of the FIFO queue
    fifo_queue.push_back(page_num);
    
    return 0;
}
