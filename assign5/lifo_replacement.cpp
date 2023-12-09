/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

// Constructor
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames), lifo_queue() {

}

// Destructor
LIFOReplacement::~LIFOReplacement() {
    // Clear the LIFO queue during destruction
    while(!lifo_queue.empty()){
        lifo_queue.pop_back();
    }
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    // Increment page fault count
    page_fault++;
    
    // Update page table entry for the new page
    page_table[page_num].valid = true;
    
    // Add the page to the back of the LIFO queue
    lifo_queue.push_back(page_num);
    
    // Update frame number in the page table
    page_table[page_num].frame_num = frame_count;
    
    // Increment the frame count
    frame_count++;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // Increment replaced page and page fault counts
    page_fault++;
    replaced_page++;
    
    // Get the index of the page at the back of the LIFO queue
    int back_index = lifo_queue.back();
    
    // Update page table entry for the victim page
    page_table[back_index].valid = false;
    
    // Remove the victim page from the LIFO queue
    lifo_queue.erase(lifo_queue.begin());
    
    // Update page table entry for the new page
    page_table[page_num].valid = true;
    
    // Add the new page to the back of the LIFO queue
    lifo_queue.push_back(page_num);
    
    return 0;
}
