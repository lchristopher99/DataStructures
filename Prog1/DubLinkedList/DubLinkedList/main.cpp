/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list to store the UID and security level of users
*/

#include "dubLinkedList.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

struct command {
    string *cmdArr;
    int caseNum;
};

// proto
command processCommand(string ans);
user createUser(command cmd);
void helpMenu();
void insert(DubLinkedList &list, command cmd);
void remove(DubLinkedList &list, command cmd);
void find(DubLinkedList &list, command cmd);
void display(DubLinkedList &list);
void load(DubLinkedList &list, command cmd);
void insertBefore(DubLinkedList &list, command cmd);
void insertAfter(DubLinkedList &list, command cmd);
bool commandSwitch(DubLinkedList &list, command cmd);
bool exit();
void invalidCommand();

int main() {
    DubLinkedList list;
    
    cout << "Welcome to the user information linked list!" << endl;
    cout << "Enter 'help' to see a list of commands." << endl;
    
    bool exitLoop = false;
    while(!exitLoop) {
        // take user answer thru call to getline to allow for easier processing
        string ans;
        getline(cin, ans);
        
        // parses command and returns appropriate switch case value
        command cmd = processCommand(ans);
        
        exitLoop = commandSwitch(list, cmd);
        cin.clear();
    }
    // if loop is exited, program terminates
    return 0;
}

// command switch
bool commandSwitch(DubLinkedList &list, command cmd) {
    switch (cmd.caseNum) {
        // help menu
        case 1: { helpMenu(); break; }
            
        // insert
        case 2: { insert(list, cmd); break; }
            
        // insert before
        case 3: { insertBefore(list, cmd); break; }
            
        // insert after
        case 4: { insertAfter(list, cmd); break; }
            
        // remove
        case 5: { remove(list, cmd); break; }
          
        // find
        case 6: { find(list, cmd); break; }
            
        // display
        case 7: { display(list); break; }
            
        // load
        case 8: { load(list, cmd); break; }
            
        // exit
        case 9: { return exit(); break; }
            
        // invalid command
        case 10: { invalidCommand(); break; }
    }
    return false;
}


// string processing
command processCommand(string ans) {
    command returnCmd;
    string cmd;
    stringstream ss(ans);
    getline(ss, cmd, ' ');
    
    int SIZE = 4;
    string cmdParam;
    string cmdArr[SIZE];
    int i = 0;
    while (ss >> cmdParam)
    {
        cmdArr[i] = cmdParam;
        i++;
    }
    
    returnCmd.cmdArr = new string[4];
    i = 0;
    while(i < 4) {
        returnCmd.cmdArr[i] = cmdArr[i];
        i++;
    }
        
    if (cmd == "help") {
        returnCmd.caseNum = 1;
        return returnCmd;
    } else if (cmd == "insert") {
        if (cmdArr[2] == "before") {
            returnCmd.caseNum = 3;
            return returnCmd;
        } else if (cmdArr[2] == "after") {
            returnCmd.caseNum = 4;
            return returnCmd;
        } else {
            returnCmd.caseNum = 2;
            return returnCmd;
        }
    } else if (cmd == "remove") {
        returnCmd.caseNum = 5;
        return returnCmd;
    } else if (cmd == "find") {
        returnCmd.caseNum = 6;
        return returnCmd;
    } else if (cmd == "display") {
        returnCmd.caseNum = 7;
        return returnCmd;
    } else if (cmd == "load") {
        returnCmd.caseNum = 8;
        return returnCmd;
    } else if (cmd == "exit") {
        returnCmd.caseNum = 9;
        return returnCmd;
    } else {
        returnCmd.caseNum = 10;
        return returnCmd;
    }
}

// creates a user struct from cmd array data
user createUser(command cmd) {
    user user;
    user.UID = cmd.cmdArr[0];
                                    
    try {
        user.securityLevel = stoi(cmd.cmdArr[1]);
    } catch (...) {
        cout << endl << "Conversion from string to int failed. Please try again..." << endl << endl;
    }
    
    return user;
}

// switch case functions
void helpMenu() {
    cout << endl;
    cout << "1 : insert <UID> <SecurityLevel> - Insert pair at tail of doubly linked list." << endl;
    cout << "2 : insert <UID> <SecurityLevel> before <UID2> - Insert pair immediately before UID2." << endl;
    cout << "3 : insert <UID> <SecurityLevel> after <UID2> - Insert pair immediately after UID2." << endl;
    cout << "4 : remove <UID> - Removes specified UID from list." << endl;
    cout << "5 : find <UID> - Find a specified UID within the list." << endl;
    cout << "6 : display - Display contents of list." << endl;
    cout << "7 : load <file> - Parse the contents of a file and create a new list." << endl;
    cout << "8 : exit - Exits program." << endl;
    cout << endl;
}

void insert(DubLinkedList &list, command cmd) {
    cout << endl << "Inserting..." << endl << endl;
    list.insert(createUser(cmd));
}

void insertBefore(DubLinkedList &list, command cmd) {
    cout << endl << "Inserting '" << cmd.cmdArr[0] << "' before '" << cmd.cmdArr[3] << "'..." << endl << endl;
    list.insertBefore(createUser(cmd), cmd.cmdArr[3]);
}

void insertAfter(DubLinkedList &list, command cmd) {
    cout << endl << "Inserting '" << cmd.cmdArr[0] << "' after '" << cmd.cmdArr[3] << "'..." << endl << endl;
    list.insertAfter(createUser(cmd), cmd.cmdArr[3]);
}

void remove(DubLinkedList &list, command cmd) {
    cout << endl << "Removing '" << cmd.cmdArr[0] << "'..." << endl << endl;
    list.remove(cmd.cmdArr[0]);
}

void find(DubLinkedList &list, command cmd) { list.find(cmd.cmdArr[0]); }

void display(DubLinkedList &list) { list.display(); }

void load(DubLinkedList &list, command cmd) {
    string filePath = cmd.cmdArr[0];
    ifstream inFile(filePath);
    if (inFile) {
        string line;
        while(getline(inFile, line)) {
            command loadedCmd = processCommand(line);
            cout << "Executing: '" << line << "'" << endl;
            
            commandSwitch(list, loadedCmd);
        }
    } else {
        cout << endl << "Invalid file path. Please try again." << endl << endl;
    }
}

bool exit() {
    cout << endl <<  "Exiting... Goodbye :)" << endl;
    return true;
}

void invalidCommand() { cout << endl << "Please enter a valid command." << endl << endl; }
