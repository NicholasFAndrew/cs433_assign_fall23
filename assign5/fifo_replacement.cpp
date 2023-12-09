/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) , fifo_queue()
{
    // TODO: Add additional implementation code
    /*for(int i = 0; i < num_frames; i++){
        fifo_queue.push_back(i);
    }*/
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
    while(!fifo_queue.empty()){
        fifo_queue.pop_back();
    }
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    page_fault++;
    page_table[page_num].valid = true;
    fifo_queue.push_back(page_num);
    page_table[page_num].frame_num = frame_count;
    frame_count++;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    page_fault++;
    int front_index = fifo_queue.front();
    page_table[front_index].valid = false;
    fifo_queue.erase(fifo_queue.begin());
    page_table[page_num].valid = true;
    fifo_queue.push_back(page_num);
    replaced_page++;
    
    return 0;
}
