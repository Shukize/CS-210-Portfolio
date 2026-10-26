// GroceryTracker.h
// CS 210 Project Three - Corner Grocer item-tracking program
// Brian Robinson
//
// Declares the GroceryTracker class. The class reads the daily purchase
// log, counts how many times each item was bought, and provides the
// lookup, list, histogram, and backup features the Corner Grocer asked for.

#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
    // Constructor stores the input and backup file names
    GroceryTracker(const std::string& inputFileName, const std::string& backupFileName);

    // Reads the input file and builds the frequency map. Returns false if the file can't be opened.
    bool LoadItems();

    // Writes every item and its count to the backup file. Returns false on failure.
    bool WriteBackupFile() const;

    // Menu Option 1: returns how many times one item was purchased (0 if not found)
    int GetItemFrequency(const std::string& itemName) const;

    // Menu Option 2: prints every item with its purchase count
    void PrintAllFrequencies() const;

    // Menu Option 3: prints every item with a row of symbols equal to its count
    void PrintHistogram(char symbol = '*') const;

    // Returns true if at least one item was loaded
    bool HasItems() const;

private:
    std::string m_inputFileName;          // file with the day's purchase records
    std::string m_backupFileName;         // backup file (frequency.dat)
    std::map<std::string, int> m_itemCounts; // item name -> times purchased (sorted A-Z)
    size_t m_longestNameLength;           // used to line up columns in the output

    // Helpers that keep the input clean and the lookups case-insensitive
    static std::string Trim(const std::string& text);
    static std::string ToLower(const std::string& text);
};

#endif // GROCERY_TRACKER_H
