/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.h
 * @author Julian Rangel & Nick F Andrew
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#pragma once

#include <vector>
using namespace std;

// A page table entry
/**
 * @brief A page table entry.
 * @details This class is used to represent a page table entry.
 * Each page has one entry in the page table, containing the following fields:
 * - frame number
 * - valid bit
 * - dirty bit (represents whether a page is changed)
 */
class PageEntry
{
public:
    // Physical frame number for a given page
    int frame_num;
    // Valid bit represents whether a page is in the physical memory
    bool valid = false;
    // Dirty bit represents whether a page is changed
    bool dirty = false;
};

/**
 * @brief A page table is like an array of page entries.
 * The size of the page table should be equal to the number of pages in logical memory.
 */
class PageTable
{
private:
    // A page table is like an array of page entries.
    vector<PageEntry> pages;

public:
    // Constructor
    /**
     * @brief Constructs a page table with the specified number of pages.
     * @param num_pages The number of pages in the page table.
     */
    PageTable(int num_pages);

    // Destructor
    /**
     * @brief Destructor for the PageTable class.
     * @details Clears the vector to release memory.
     */
    ~PageTable();

    // Vector containing page entries
    vector<PageEntry> page_vector;

    /**
     * @brief Inserts a specified number of page entries into the page table.
     * @param size The number of page entries to insert.
     */
    void insert(int size);

    /**
     * @brief Overloaded operator to access a page in the page table.
     * @param i The index of the page to access.
     * @return A reference to the page entry at the specified index.
     */
    PageEntry& operator[](int i) {
        return pages[i];
    }
};
