// GroceryTracker.cpp
// Implementation of the GroceryTracker class.

#include "GroceryTracker.h"

#include <cctype>
#include <fstream>
#include <iostream>

// Capitalizes the first letter and lowercases the rest so that
// user input matches the format used in the input file.
std::string GroceryTracker::Normalize(const std::string& text) {
    std::string result = text;
    for (std::size_t i = 0; i < result.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(result[i]);
        result[i] = static_cast<char>(i == 0 ? std::toupper(c) : std::tolower(c));
    }
    return result;
}

bool GroceryTracker::LoadFromFile(const std::string& inputFileName) {
    std::ifstream inFile(inputFileName);
    if (!inFile.is_open()) {
        return false;
    }

    itemCounts_.clear();  // Start fresh in case this is called twice

    std::string item;
    while (inFile >> item) {
        // operator[] creates the entry at 0 if new, then we increment it
        ++itemCounts_[Normalize(item)];
    }

    inFile.close();
    return true;
}

bool GroceryTracker::WriteBackupFile(const std::string& backupFileName) const {
    std::ofstream outFile(backupFileName);
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& entry : itemCounts_) {
        outFile << entry.first << " " << entry.second << "\n";
    }

    outFile.close();
    return true;
}

int GroceryTracker::GetFrequency(const std::string& item) const {
    auto found = itemCounts_.find(Normalize(item));
    return (found != itemCounts_.end()) ? found->second : 0;
}

void GroceryTracker::PrintFrequencies() const {
    for (const auto& entry : itemCounts_) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

void GroceryTracker::PrintHistogram() const {
    for (const auto& entry : itemCounts_) {
        // std::string(count, '*') builds a run of asterisks of that length
        std::cout << entry.first << " " << std::string(entry.second, '*') << std::endl;
    }
}
