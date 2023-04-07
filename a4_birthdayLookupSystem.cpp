// Kevin Tian
// 301552372
// kta101

#include "a4_birthdaylib.hpp"
#include "a4_birthdayBST.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    cout << "+================================================+" << endl;
    cout << "|-------- Famous Birthdays Lookup System --------|" << endl;
    cout << "|------------------ Kevin Tian ------------------|" << endl;
    cout << "|------------------- 301552372 ------------------|" << endl;
    cout << "|----------------- kta101@sfu.ca ----------------|" << endl;
    cout << "+================================================+" << endl;

    short year, month, day;
    string year_str, month_str, day_str, name, knownFor;
    string line, filename;
    BirthdayBST birthdayBST;
    ifstream myfile;
    ofstream userfile(filename);
    bool loaded = false;
    int choice;
    int entries;

    do {
        // print out menu options
        cout << "Press numbers 1-6 for the following options and then enter: " << endl;
        cout << "1) to load a birthday file." << endl;
        cout << "2) to list birthdays sorted by Month-Day." << endl;
        cout << "3) to lookup a birthday." << endl;
        cout << "4) to add a birthday." << endl;
        cout << "5) to save a birthday file." << endl;
        cout << "6) to terminate the program." << endl;

        // prompt user for choice
        cout << "Option: ";
        cin >> choice;

        // execute corresponding code based on choice
        switch(choice){
            case 1:
                cout << "Enter the full name of the birthday file (with extension): ";
                cin >> filename;
                myfile.open(filename);
                // if file fails to open, print error message and break
                if (!myfile.good()){
                    cout << "Failed to open file. Check if it exists." << endl;
                    cout << "=============================================" << endl;
                    break;
                }
                else{
                    // if file successfully loads, set loaded to true and clear the BST
                    loaded = true;
                    birthdayBST.~BirthdayBST();
                    // keep track of number of entries in file
                    entries = 0;

                    // read the myfile line by line
                    while (getline(myfile, line)){
                        string year_str, month_str, day_str;
                        // initialize counter for the number of '-' delimiters read
                        int delimiter_count = 0;
                        // iterate over each character in the input line
                        for (char c : line) {
                            // if a '-' delimiter is read, increment delimiter_count and continue to next character
                            if (c == '-') {
                                delimiter_count++;
                                continue;
                            }
                            // append the current character to the correct string based on delimiter_count
                            if (delimiter_count == 0) {
                                year_str += c;
                            } else if (delimiter_count == 1) {
                                month_str += c;
                            } else {
                                day_str += c;
                            }
                        }

                        // store year, month, and day as integers
                        int year = stoi(year_str);
                        int month = stoi(month_str);
                        int day = stoi(day_str);

                        // read and store name and knownFor
                        string name, knownFor;
                        getline(myfile, name);
                        getline(myfile, knownFor);

                        // create a new birthday object and add it into the BST
                        Birthday* newBDay = create_Birthday(year, month, day, name, knownFor);
                        birthdayBST.insertNode(newBDay);

                        entries++;
                        getline(myfile, line); // ignore the separator line
                    }

                    myfile.close();
                    cout << entries << " entries read." << endl;
                    cout << "=============================================" << endl;
                }
                break;
            
            case 2:
                if(!loaded){
                    cout <<"No birthday file loaded. Load one first." << endl;
                    cout <<"=============================================" << endl;
                    break;
                }
                // birthdays are already sorted by month-day when they are added into the BST, so call inOrderPrint
                birthdayBST.inOrderPrint(cout);
                break;
            
            case 3:
                if(!loaded){
                    cout <<"No birthday file loaded. Load one first." << endl;
                    cout <<"=============================================" << endl;
                    break;
                }
                cout << "What is the month? (Input 1-12 and press enter)? ";
                cin >> month_str;
                cout << "What is the day? (Input 1-31 and press enter)? ";
                cin >> day_str;

                // store month and day as integers
                month = stoi(month_str);
                day = stoi(day_str);

                // if there are no matching birthdays, print no such birthday and break
                if (birthdayBST.findNodeByMD(month, day) == nullptr){
                    cout << "No such birthday on record." << endl;
                    cout << "=============================================" << endl;
                    break;
                }
                // report all entries with the entered birthday.
                else{
                    birthdayBST.printAllNodeWithMatchingMD(month, day, cout);
                }
                break;

            case 4:
                if(!loaded){
                    cout <<"No birthday file loaded. Load one first." << endl;
                    cout <<"=============================================" << endl;
                    break;
                }
                cout << "What is the year? (Input a 4-digit year): ";
                cin >> year_str;
                year = stoi(year_str);

                cout << "What is the month? (Input 1-12 and press enter): ";
                cin >> month_str;
                month = stoi(month_str);

                cout << "What is the day? (Input 1-31 and press enter): ";
                cin >> day_str;
                day = stoi(day_str);

                cin.ignore();

                cout << "What is the name of the person? ";
                getline(cin, name);

                cout << "What is the person known for? ";
                getline(cin, knownFor);

                cout << "You have entered: " << year_str << "-" << month_str << "-" << day_str 
                << endl << name << endl << knownFor << endl;
                
                // if a duplicate is found in BST, print error message
                if (birthdayBST.findNodeByYMDN(year, month, day, name) != nullptr){
                    cout << "An entry with the same birthday and name already exists. Nothing added." << endl;
                    cout << "=============================================" << endl;
                    break;
                }
                // if no duplicate entry is found, create a new birthday object and add it into the BST
                else{
                    Birthday* newBDay = create_Birthday(year, month, day, name, knownFor);
                    birthdayBST.insertNode(newBDay);
                    entries++;
                    cout << "Birthday added." << endl;
                    cout << "=============================================" << endl;
                }
                break;

            case 5:
                cout << "Enter the full name of the birthday file (with extension): " << endl;
                cin >> filename;
                // open the file and call inOrderPrint to print the formatted entries into the file
                userfile.open(filename);
                birthdayBST.inOrderPrint(userfile);
                userfile.close();    
                cout << entries << " entries added to " << filename << endl;
                break;

            case 6:
                birthdayBST.~BirthdayBST(); // clear the BST
                cout << "Thank you for using 'Famous Birthdays Lookup System'. Goodbye!";
                break;
        }
    
    } while (choice != 6);
    
    return 0;
}