// main.cpp
// Corner Grocer item-tracking program: menu and user interaction.

#include <iostream>
#include <limits>
#include <string>

#include "GroceryTracker.h"

const std::string INPUT_FILE = "CS210_Project_Three_Input_File.txt";
const std::string BACKUP_FILE = "frequency.dat";

// Prints the menu options.
static void PrintMenu() {
    std::cout << "\n===== Corner Grocer =====\n"
              << "1. Look up an item's frequency\n"
              << "2. Print all item frequencies\n"
              << "3. Print histogram\n"
              << "4. Exit\n"
              << "Enter your choice (1-4): ";
}

// Reads a menu choice and validates it. Returns 0 for invalid input.
static int ReadMenuChoice() {
    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();  // Clear the error state from non-numeric input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int main() {
    GroceryTracker tracker;

    // Load the purchase log; exit early if the file is missing.
    if (!tracker.LoadFromFile(INPUT_FILE)) {
        std::cerr << "Error: could not open " << INPUT_FILE << "." << std::endl;
        return 1;
    }

    // Create the backup file automatically at startup (no user action needed).
    if (!tracker.WriteBackupFile(BACKUP_FILE)) {
        std::cerr << "Warning: could not write " << BACKUP_FILE << "." << std::endl;
    }

    int choice = 0;
    while (choice != 4) {
        PrintMenu();
        choice = ReadMenuChoice();

        switch (choice) {
        case 1: {
            std::string item;
            std::cout << "Enter the item to look up: ";
            std::cin >> item;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << item << " " << tracker.GetFrequency(item) << std::endl;
            break;
        }
        case 2:
            tracker.PrintFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number from 1 to 4." << std::endl;
            break;
        }
    }
    return 0;
}
