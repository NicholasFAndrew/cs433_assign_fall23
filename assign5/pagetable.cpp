/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author ??? (TODO: your name)
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

// TODO: Add your implementation of PageTable
// Constrcutor
// TODO: Add your code
PageTable::PageTable(int num_pages) {
    for(int i = 0; i < num_pages; i++){
        PageEntry page;
        pages.push_back(page);
    }
}

// Destructor
// TODO: Add your code
PageTable::~PageTable() {
    while(!pages.empty()){
        pages.pop_back();
    }
}
