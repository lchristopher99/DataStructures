/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes priority queue in order to simulate an ER.
*/

#include <sstream>
#include <iostream>
#include <fstream>
#include "MaxHeap.h"
#include "patient.h"
using namespace std;

struct command {
    string *cmdArr;
    int caseNum;
};

// main helper functions
bool commandSwitch(MaxHeap &h, command cmd);
void load(MaxHeap &h, command cmd);
command processCommand(string ans);
int toInt(string val);
void invalidCommand();
void helpMenu();
bool exit();

// max heap helper functions
command processAdmitCommand(string ans);
bool admitCommandSwitch(MaxHeap &h, command cmd, patient &p);
void admit(MaxHeap &h, string lName, string fName);
bool timda(MaxHeap &h, patient &p);

int main() {
    cout << "What is the max number of patients for the priority queue? ";
    
    int maxNum;
    cin >> maxNum;
    while (!cin) {
        cout << endl << "Please enter an integer..." << endl;
        cout << "What is the max number of patients for the priority queue? ";
        cin.clear();
        cin.ignore();
        cin >> maxNum;
    }
    
    MaxHeap h(maxNum);
    
    cin.ignore();
    
    cout << "Enter 'help' to see a list of commands." << endl;

    bool exitLoop = false;
    while(!exitLoop) {
        // take user answer thru call to getline to allow for easier processing
        string ans;
        getline(cin, ans);

        // parses command and returns appropriate switch case value
        command cmd = processCommand(ans);

        exitLoop = commandSwitch(h, cmd);
        cin.clear();
    }
    // if loop is exited, program terminates
    return 0;
}

// main helper functions

// command switch
bool commandSwitch(MaxHeap &h, command cmd) {
    switch (cmd.caseNum) {
        // help menu
        case 1: { helpMenu(); cout << endl; break; }
            
        // admit <last name> <first name>
        case 2: { admit(h, cmd.cmdArr[0], cmd.cmdArr[1]); cout << endl; break; }

        // next
        case 3: {
            patient remPat = h.removeMax();
            cout << endl << "Following patient has been removed:" << endl;

            cout << "Name: " << remPat.lName << ", " << remPat.fName << endl;
            cout << "Priority: " << remPat.priority << endl;
            cout << "Ticket: " << remPat.TicketNum << endl;
            cout << "Complaint: " << remPat.complaint << endl;
            cout << "Symptoms: ";
            int i = 0;
            while (i <= 20 && remPat.symptoms[i] != "") {
                cout << remPat.symptoms[i] << ", ";
                i++;
            }
            
            cout << endl << endl;
            break;
        }

        // display
        case 4: {
            patient currPat = h.getMax();
            cout << endl << "Current Patient:" << endl;

            cout << "Name: " << currPat.lName << ", " << currPat.fName << endl;
            cout << "Priority: " << currPat.priority << endl;
            cout << "Ticket: " << currPat.TicketNum << endl;
            cout << "Complaint: " << currPat.complaint << endl;
            cout << "Symptoms: ";
            int i = 0;
            while (i <= 20 && currPat.symptoms[i] != "") {
                cout << currPat.symptoms[i] << ", ";
                i++;
            }
            
            cout << endl << endl;
            break;
        }
            
        // load
        case 5: { cout << endl; break; }

        // exit
        case 6: { return exit(); break; }
            
        // invalid command
        case 7: { invalidCommand(); cout << endl; break; }
    }
    return false;
}

// string processing
command processCommand(string ans) {
    command returnCmd;
    string cmd;
    stringstream ss(ans);
    getline(ss, cmd, ' ');
    
    int SIZE = 3;
    string cmdParam;
    returnCmd.cmdArr = new string[SIZE];
    int i = 0;
    while (ss >> cmdParam) {
        returnCmd.cmdArr[i] = cmdParam;
        i++;
    }
        
    if (cmd == "help") {
        returnCmd.caseNum = 1;
        return returnCmd;
    } else if (cmd == "admit") {
        returnCmd.caseNum = 2;
        return returnCmd;
    } else if (cmd == "next") {
        returnCmd.caseNum = 3;
        return returnCmd;
    } else if (cmd == "display") {
        returnCmd.caseNum = 4;
        return returnCmd;
    } else if (cmd == "load") {
        returnCmd.caseNum = 5;
        return returnCmd;
    } else if (cmd == "exit") {
           returnCmd.caseNum = 6;
           return returnCmd;
    } else { // invalid command
        returnCmd.caseNum = 7;
        return returnCmd;
    }
}

// attempts to convert string to int, throws exception if fail
int toInt(string val) {
    int value;
    try {
        value = stoi(val);
    } catch (...) {
        cout << endl << "Conversion from string to int failed. Please try again..." << endl << endl;
    }

    return value;
}

// switch case functions
void helpMenu() {
    cout << endl;
    cout << "1 : admit <last name> <first name> - Begins the admission process for patient <first name> <last name>." << endl;
    cout << "2 : set complaint <complaint> - (100 word limit) Adds a description of the complaint to the patient record." << endl;
    cout << "3 : add symptom <symptom> - (20 symptom limit) Adds a symptom to the open patient record." << endl;
    cout << "4 : set priority <priority> - Sets the priority level to ambulatory, non-urgent, urgent, critical, or code." << endl;
    cout << "5 : timda - Closes the current patient record and adds it to the priority queue." << endl;
    cout << "6 : next – Removes the current patient and moves the next patient in the priority queue to the top." << endl;
    cout << "7 : display – Displays the patient record for the patient at the top of the priority queue." << endl;
    cout << "8 : load <file> - Parses the contents of a file as if they were entered from the command line." << endl;
    cout << "9 : exit - Exits program." << endl;
}

void invalidCommand() { cout << endl << "Please enter a valid command." << endl; }

void load(MaxHeap &h, command cmd) {
    string filePath = cmd.cmdArr[0];
    ifstream inFile(filePath);
    if (inFile) {
        string line;
        while(getline(inFile, line)) {
            command loadedCmd = processCommand(line);
            cout << "Executing: '" << line << "'" << endl;

            commandSwitch(h, loadedCmd);
        }
    } else {
        cout << endl << "Invalid file path. Please try again." << endl << endl;
    }
}

bool exit() {
    cout << endl <<  "Exiting... Goodbye :)" << endl;
    return true;
}

// max heap helper functions

command processAdmitCommand(string ans) {
    command returnCmd;
    string cmd;
    stringstream ss(ans);
    getline(ss, cmd, ' ');
    
    int SIZE = 100;
    string cmdParam;
    returnCmd.cmdArr = new string[SIZE];
    int i = 0;
    while (ss >> cmdParam) {
        returnCmd.cmdArr[i] = cmdParam;
        i++;
    }
        
    if (cmd == "set") {
        if (returnCmd.cmdArr[0] == "complaint") {
            returnCmd.caseNum = 1;
            return returnCmd;
        } else if (returnCmd.cmdArr[0] == "priority") {
            returnCmd.caseNum = 2;
            return returnCmd;
        } else {
            returnCmd.caseNum = 5;
            return returnCmd;
        }
    } else if (cmd == "add") {
        if (returnCmd.cmdArr[0] == "symptom") {
            returnCmd.caseNum = 3;
            return returnCmd;
        } else {
            returnCmd.caseNum = 5;
            return returnCmd;
        }
    } else if (cmd == "timda") {
        returnCmd.caseNum = 4;
        return returnCmd;
    } else {
        returnCmd.caseNum = 5;
        return returnCmd;
    }
}

bool admitCommandSwitch(MaxHeap &h, command cmd, patient &p) {
    switch (cmd.caseNum) {
        // set complaint <complaint>
        case 1: {
            int i = 1;
            while (i <= 100 && cmd.cmdArr[i] != "") {
                p.complaint += cmd.cmdArr[i] + " ";
                i++;
            }
            cout << endl;
            break;
        }

        // set priority <priority>
        case 2: { p.priority = cmd.cmdArr[1]; cout << endl; break; }
            
        // add symptom <symptom>
        case 3: {
            int i = 0;
            int j = 1;
            while (i <= 20) {
                if (p.symptoms[i] != "") {
                    i++;
                } else {
                    while (j <= 100 && cmd.cmdArr[j] != "") {
                        p.symptoms[i] += cmd.cmdArr[j] + " ";
                        j++;
                    }
                    break;
                }
            }
            cout << endl;
            break;
        }

        // timda
        case 4: { return timda(h, p); }
            
        // invalid command
        case 5: { invalidCommand(); cout << endl; break; }
    }
    return false;
}

void admit(MaxHeap &h, string lName, string fName) {
    cout << endl << "Creating a patient record for " << lName << ", " << fName << endl;

    patient currPat;
    int ticketNum = h.getCurrSize() + 1;
    currPat.fName = fName;
    currPat.lName = lName;
    currPat.priority = "ambulatory";
    currPat.TicketNum = ticketNum;
    
    cout << "Priority: ambulatory" << endl;
    cout << "Ticket: " << ticketNum << endl;
    cout << "Please add a description of the complaint and any reported symptoms." << endl << endl;
    
    bool exitLoop = false;
    while(!exitLoop) {
        // take user answer thru call to getline to allow for easier processing
        string ans;
        getline(cin, ans);

        // parses command and returns appropriate switch case value
        command cmd = processAdmitCommand(ans);

        exitLoop = admitCommandSwitch(h, cmd, currPat);
        cin.clear();
    }
}

bool timda(MaxHeap &h, patient &p) {
    cout << endl << "Closing current patient record and adding to queue..." << endl;
    h.insertPatient(p);
    return true;
}
