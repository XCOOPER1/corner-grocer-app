#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream> // For std::istringstream

using namespace std;

class ItemTracker {
private:
    map<string, int> itemFrequencies;

    // New method to read the input file line by line
    void readInputFile() {
        ifstream inputFile("CS210_Project_Three_Input_File.txt");
        string line;
        while (getline(inputFile, line)) { // Read file line by line
            istringstream lineStream(line); // Use istringstream to parse the line
            string item;
            int count;
            if (lineStream >> item >> count) { // Parse item and count from the line
                itemFrequencies[item] += count; // Accumulate item frequencies
            }
        }
        inputFile.close();
    }

    // Create a backup file with the current item frequencies
    void createBackupFile() {
        ofstream outputFile("frequency.dat");
        for (const auto& pair : itemFrequencies) {
            outputFile << pair.first << " " << pair.second << endl;
        }
        outputFile.close();
    }

public:
    // Constructor to initialize the ItemTracker object
    ItemTracker() {
        readInputFile(); // Read the input file upon object creation
        createBackupFile(); // Create a backup file upon object creation
    }

    // Method to find and display the frequency of a specified item
    void findItemFrequency(const string& item) {
        if (itemFrequencies.find(item) != itemFrequencies.end()) {
            cout << item << ": " << itemFrequencies[item] << endl;
        }
        else {
            cout << "Item not found.\n";
        }
    }

    // Method to print the frequency of all items
    void printAllItemsFrequency() {
        for (const auto& pair : itemFrequencies) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Method to print a histogram of item frequencies
    void printHistogram() {
        for (const auto& pair : itemFrequencies) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*"; // Use asterisks to represent the frequency
            }
            cout << endl;
        }
    }
};

int main() {
    ItemTracker tracker; // Create an ItemTracker object
    int choice;

    do {
        // Display menu options
        cout << "\nMenu:\n"
            << "1. Find item frequency\n"
            << "2. Print all items frequency\n"
            << "3. Print histogram\n"
            << "4. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item name: ";
            cin >> item; // Get the item name from the user
            tracker.findItemFrequency(item); // Find and display the item's frequency
            break;
        }
        case 2:
            tracker.printAllItemsFrequency(); // Print the frequency of all items
            break;
        case 3:
            tracker.printHistogram(); // Print a histogram of item frequencies
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4); // Loop until the user chooses to exit

    return 0;
}
