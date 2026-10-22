// GroceryTracker.h
// Tracks how often each grocery item appears in a daily purchase log.

#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
    // Reads the input file and builds the frequency map.
    // Returns false if the file could not be opened.
    bool LoadFromFile(const std::string& inputFileName);

    // Writes every item and its count to the backup file (frequency.dat).
    // Returns false if the file could not be written.
    bool WriteBackupFile(const std::string& backupFileName) const;

    // Returns how many times an item was purchased (0 if never seen).
    int GetFrequency(const std::string& item) const;

    // Prints "item count" for every item.
    void PrintFrequencies() const;

    // Prints "item ****" for every item, one asterisk per purchase.
    void PrintHistogram() const;

private:
    // Normalizes text so lookups are case-insensitive ("apples" -> "Apples").
    static std::string Normalize(const std::string& text);

    std::map<std::string, int> itemCounts_;  // item name -> purchase count
};

#endif
