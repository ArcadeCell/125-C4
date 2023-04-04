// Kevin Tian
// 301552372
// kta101

#include "a4_birthdaylib.hpp"
#include "a4_birthdayBST.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    cout << "+================================================+" << endl;
    cout << "|-------- Famous Birthdays Lookup System --------|" << endl;
    cout << "|------------------ Kevin Tian ------------------|" << endl;
    cout << "|------------------- 301552372 ------------------|" << endl;
    cout << "|----------------- kta101@sfu.ca ----------------|" << endl;
    cout << "+================================================+" << endl;

    // int used = 0;
    // int capacity = 16;
    // Birthday **bdayArray = new Birthday*[capacity];
    short year, month, day;
    string year_str, month_str, day_str, name, knownFor;
    string line;
    string filename;
    BirthdayBST birthdayBST;
    ifstream myFile;
    bool loaded = false;
    int choice;

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
                myFile.open(filename);
                // if file fails to open, print error message and break
                if (!myFile.good()){
                    cout << "Failed to open file. Please try again." << endl;
                    cout << "=============================================" << endl;
                    break;
                }
                else{
                    // if file successfully loads, set loaded to true and clear the BST
                    loaded = true;
                    birthdayBST.~BirthdayBST();
                    // keep track of number of entries in file
                    int entries = 0;

                    while (getline(myFile, line)){
                        // read year, month, and day
                        stringstream iss(line);
                        getline(iss, year_str, '-');
                        getline(iss, month_str, '-');
                        getline(iss, day_str);
                        // store year, month, and day as integers
                        year = stoi(year_str);
                        month = stoi(month_str);
                        day = stoi(day_str);
                        // read and store name and knownFor
                        getline(myFile, name);
                        getline(myFile, knownFor);

                        // create a new birthday object and add it into the BST
                        Birthday* newBDay = create_Birthday(year, month, day, name, knownFor);
                        birthdayBST.insertNode(newBDay);

                        entries++;
                        getline(myFile, line); // ignore the separator line
                    }
                    myFile.close();
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
                birthdayBST.inOrderPrint(cout);
                break;
            
            case 3:
                if(!loaded){
                    cout <<"No birthday file loaded. Load one first." << endl;
                    cout <<"=============================================" << endl;
                    break;
                }
                // prompt user for month and day
                cout << "What is the month? (Input 1-12 and press enter)? ";
                cin >> month_str;

                cout << "What is the day? (Input 1-31 and press enter)? ";
                cin >> day_str;
                // store month and day as integers
                month = stoi(month_str);
                day = stoi(day_str);
                // if there are no matching birthdays, no birthdays and break
                if (birthdayBST.findNodeByMD(month, day) == nullptr){
                    cout << "No such birthday on record." << endl;
                    cout << "=============================================" << endl;
                    break;
                }
                // report all entries with the entered birthday.
                else{
                    birthdayBST.findNodeByMD(month, day);
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
                
                // if an entry with the year, month, day, and name already exists in BST, print error message{
                if (birthdayBST.findNodeByYMDN(year, month, day, name) != nullptr){
                    cout << "An entry with the same birthday and name already exists. Nothing added." << endl;
                    cout << "=============================================" << endl;
                }
                // if no duplicate entry is found, create a new birthday object and add it into the BST
                else{
                    Birthday* newBDay = create_Birthday(year, month, day, name, knownFor);
                    birthdayBST.insertNode(newBDay);
                    cout << "Birthday added." << endl;
                    cout << "=============================================" << endl;
                }
                break;

            case 5:
                if(!loaded){
                    cout <<"No birthday file loaded. Load one first." << endl;
                    cout <<"=============================================" << endl;
                    break;
                }
                break;

            case 6:
                // for (int i = 0; i < used; i++){
                //     delete_Birthday(bdayArray[i]);
                // }
                cout << "Thank you for using 'Famous Birthdays Lookup System'. Goodbye!";
                break;
        }
    
    } while (choice != 6);
    
    return 0;
}