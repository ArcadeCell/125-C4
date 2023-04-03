#include "a4_birthdaylib.hpp"

Birthday* create_Birthday(short year, short month, short day, string name, string knownFor){
    Birthday* bDay = new Birthday;
    bDay->year = year;
    bDay->month = month;
    bDay->day = day;
    bDay->name = name;
    bDay->knownFor = knownFor;
    return bDay;
}

void delete_Birthday(Birthday* person){
    if(person != NULL){
        delete person;
    }
}

void print_Birthday(Birthday* person, ostream& os){
    os << person->year << "-" << person->month << "-" << person->day << endl
    << person->name << endl << person->knownFor << endl 
    << "=============================================" << endl;
}

int compareBirthdaysByMD(const Birthday* p1, const Birthday* p2){
    if(p1->month < p2->month) return -1;
    else if(p1->month > p2->month) return 1;
    else{
        if (p1->day < p2->day) return -1;
        else if (p1->day > p2->day) return 1;
        else return 0;  
    }
}