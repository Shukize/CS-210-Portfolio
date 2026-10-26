// GroceryTracker.cpp
// CS 210 Project Three - Corner Grocer item-tracking program
// Brian Robinson
//
// Defines the GroceryTracker class member functions.

#include "GroceryTracker.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Constructor - saves the file names and starts with an empty map
GroceryTracker::GroceryTracker(const string& inputFileName, const string& backupFileName)
    : m_inputFileName(inputFileName),
      m_backupFileName(backupFileName),
      m_longestNameLength(0) {
}

// Reads one item per line and adds 1 to that item's count in the map
bool GroceryTracker::LoadItems() {
    ifstream inputFile(m_inputFileName);

    // Stop early if the file is missing or can't be opened
    if (!inputFile.is_open()) {
        cerr << "Error: could not open input file \"" << m_inputFileName << "\"." << endl;
        return false;
    }

    m_itemCounts.clear();
    m_longestNameLength = 0;

    string line;
    while (getline(inputFile, line)) {
        string itemName = Trim(line);   // removes stray spaces and Windows \r endings

        if (itemName.empty()) {
            continue;                   // skip blank lines
        }

        m_itemCounts[itemName]++;       // map creates the key at 0 if it's new, then adds 1

        if (itemName.length() > m_longestNameLength) {
            m_longestNameLength = itemName.length();
        }
    }

    inputFile.close();
    return true;
}

// Writes "Item Count" pairs to frequency.dat for backup
bool GroceryTracker::WriteBackupFile() const {
    ofstream backupFile(m_backupFileName);

    if (!backupFile.is_open()) {
        cerr << "Error: could not create backup file \"" << m_backupFileName << "\"." << endl;
        return false;
    }

    for (const auto& item : m_itemCounts) {
        backupFile << item.first << " " << item.second << endl;
    }

    backupFile.close();
    return true;
}

// Looks up one item. Comparison ignores case so "apples" matches "Apples".
int GroceryTracker::GetItemFrequency(const string& itemName) const {
    string searchName = ToLower(Trim(itemName));

    for (const auto& item : m_itemCounts) {
        if (ToLower(item.first) == searchName) {
            return item.second;
        }
    }

    return 0;   // item was never purchased
}

// Prints each item and its count in two lined-up columns
void GroceryTracker::PrintAllFrequencies() const {
    int fieldWidth = static_cast<int>(m_longestNameLength) + 2;

    for (const auto& item : m_itemCounts) {
        cout << left << setw(fieldWidth) << item.first << right << item.second << endl;
    }
}

// Prints each item followed by one symbol per purchase
void GroceryTracker::PrintHistogram(char symbol) const {
    int fieldWidth = static_cast<int>(m_longestNameLength) + 2;

    for (const auto& item : m_itemCounts) {
        cout << left << setw(fieldWidth) << item.first << right
             << string(item.second, symbol) << endl;   // string(n, c) builds n copies of c
    }
}

bool GroceryTracker::HasItems() const {
    return !m_itemCounts.empty();
}

// Removes spaces, tabs, and \r from both ends of a string
string GroceryTracker::Trim(const string& text) {
    const string whitespace = " \t\r\n";
    size_t start = text.find_first_not_of(whitespace);

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

// Returns a lowercase copy of a string for case-insensitive comparisons
string GroceryTracker::ToLower(const string& text) {
    string result = text;
    for (char& letter : result) {
        letter = static_cast<char>(tolower(static_cast<unsigned char>(letter)));
    }
    return result;
}
