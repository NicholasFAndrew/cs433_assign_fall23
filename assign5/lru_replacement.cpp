/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"
#include "algorithm"

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) {

}

// Destructor
LRUReplacement::~LRUReplacement() {

}

// Access a page already in physical memory
void LRUReplacement::touch_page(int page_num) {
    // Check if the page is in the LRU map
    auto it = lru_map.find(page_num);
    if (it != lru_map.end()) {
        // Page is in the LRU map, update its position in the queue
        lru_queue.erase(it->second);
        lru_queue.push_front(page_num);
        lru_map[page_num] = lru_queue.begin();
    }
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {

    // Increment page fault count
    page_fault++;
    
    // Calculate the frame number
    int frame_num = frame_total - frame_count;
    
    // Update the page table entry
    page_table[page_num].frame_num = frame_num;
    page_table[page_num].valid = true;
    
    // Add the page to the front of the LRU queue
    lru_queue.push_front(page_num);
    lru_map[page_num] = lru_queue.begin();
    
    // Increment the frame count
    frame_count++;
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // Increment replaced page and page fault counts
    replaced_page++;
    page_fault++;
    
    // Get the victim page from the back of the LRU queue
    int victim = lru_queue.back();
    int frame_num = page_table[victim].frame_num;

    // Remove the victim page from the LRU data structures
    lru_queue.pop_back();
    lru_map.erase(victim);
    
    // Add the new page to the front of the LRU queue
    lru_queue.push_front(page_num);
    lru_map[page_num] = lru_queue.begin();

    // Update page table entries for the new and victim pages
    page_table[page_num].frame_num = frame_num;
    page_table[page_num].valid = true;
    page_table[victim].valid = false;
    
    return 0;
}
