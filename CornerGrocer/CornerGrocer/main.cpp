// main.cpp
// CS 210 Project Three - Corner Grocer item-tracking program
// Brian Robinson
//
// Loads the purchase records, backs them up to frequency.dat right away,
// then runs the menu loop until the user picks option 4.

#include <iostream>
#include <limits>
#include <string>

#include "GroceryTracker.h"

using namespace std;

// File names used by the program
const string INPUT_FILE_NAME = "CS210_Project_Three_Input_File.txt";
const string BACKUP_FILE_NAME = "frequency.dat";

// Menu option numbers so the switch reads clearly
const int MENU_SEARCH_ITEM = 1;
const int MENU_PRINT_LIST = 2;
const int MENU_PRINT_HISTOGRAM = 3;
const int MENU_EXIT = 4;

// Prints the main menu
void DisplayMenu() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "        Corner Grocer Item Tracker      " << endl;
    cout << "========================================" << endl;
    cout << "  1. Look up how often an item was bought" << endl;
    cout << "  2. Print purchase counts for all items" << endl;
    cout << "  3. Print purchase histogram" << endl;
    cout << "  4. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (1-4): ";
}

// Reads a whole number from the user and keeps asking until it's valid
int GetMenuChoice() {
    int choice;

    while (true) {
        if (cin >> choice) {
            // Throw away anything typed after the number (like "2abc")
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice >= MENU_SEARCH_ITEM && choice <= MENU_EXIT) {
                return choice;
            }
            cout << "That option isn't on the menu. Please enter 1, 2, 3, or 4: ";
        }
        else {
            if (cin.eof()) {
                return MENU_EXIT;   // input stream closed, so exit cleanly
            }
            // Non-number entered: reset cin and clear the bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4: ";
        }
    }
}

// Menu Option 1: asks for an item and shows how many were bought
void HandleItemSearch(const GroceryTracker& tracker) {
    string itemName;

    cout << "Enter the item you want to look up: ";
    getline(cin, itemName);

    // Make sure the user actually typed something
    while (itemName.find_first_not_of(" \t") == string::npos) {
        if (cin.eof()) {
            return;
        }
        cout << "Item name can't be blank. Please enter an item: ";
        getline(cin, itemName);
    }

    int frequency = tracker.GetItemFrequency(itemName);
    cout << endl << itemName << " was purchased " << frequency
         << (frequency == 1 ? " time." : " times.") << endl;
}

int main() {
    GroceryTracker tracker(INPUT_FILE_NAME, BACKUP_FILE_NAME);

    // Load the data first - nothing else works without it
    if (!tracker.LoadItems()) {
        cerr << "Make sure " << INPUT_FILE_NAME
             << " is in the same folder as the program and try again." << endl;
        return 1;
    }

    if (!tracker.HasItems()) {
        cerr << "The input file is empty, so there is nothing to track." << endl;
        return 1;
    }

    // Create the backup file at startup with no user input needed
    if (tracker.WriteBackupFile()) {
        cout << "Backup saved to " << BACKUP_FILE_NAME << "." << endl;
    }

    int userChoice = 0;

    // Main menu loop - runs until the user picks Exit
    while (userChoice != MENU_EXIT) {
        DisplayMenu();
        userChoice = GetMenuChoice();
        cout << endl;

        switch (userChoice) {
        case MENU_SEARCH_ITEM:
            HandleItemSearch(tracker);
            break;
        case MENU_PRINT_LIST:
            cout << "Item Purchase Counts" << endl;
            cout << "--------------------" << endl;
            tracker.PrintAllFrequencies();
            break;
        case MENU_PRINT_HISTOGRAM:
            cout << "Item Purchase Histogram" << endl;
            cout << "-----------------------" << endl;
            tracker.PrintHistogram('*');
            break;
        case MENU_EXIT:
            cout << "Thanks for using the Corner Grocer Item Tracker. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}
