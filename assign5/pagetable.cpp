/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) {
    // Initialize the page table with the specified number of pages
    for (int i = 0; i < num_pages; i++) {
        PageEntry page;
        pages.push_back(page);
    }
}

// Destructor
PageTable::~PageTable() {
    // Clean up memory by removing all elements from the vector
    while (!pages.empty()) {
        pages.pop_back();
    }
}
