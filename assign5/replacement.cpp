/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
    // Initialize the Replacement object with the specified number of pages and frames
    page_total = num_pages;
    frame_total = num_frames;
    reference = 0;
    page_fault = 0;
    replaced_page = 0;
    frame_count = 0;
}

// Destructor
Replacement::~Replacement()
{

}

// Simulate a single page access
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    // Simulates a single page access based on page replacement algorithm rules

    // Increment the reference counter for each page access
    reference++;

    // If the page is not valid and there are free frames, load the page
    if (!page_table[page_num].valid && frame_count < frame_total) {
        load_page(page_num);
        return true;
    }
    // If the page is not valid and there are no free frames, replace the page
    else if (!page_table[page_num].valid && frame_count >= frame_total) {
        replace_page(page_num);
        return true;
    }
    // If the page is valid, update its status
    else {
        touch_page(page_num);
    }

    // It's not a page fault
    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
    // Print the simulation statistics
    std::cout << "Number of references: \t\t" << reference << std::endl;
    std::cout << "Number of page faults: \t\t" << page_fault << std::endl;
    std::cout << "Number of page replacements: \t" << replaced_page << std::endl;
}
