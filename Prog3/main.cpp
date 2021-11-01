/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a BST alongside a STL list in order to organize a closet with mentioned data structures
*/

#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include "BST.h"
using namespace std;

struct command {
    string *cmdArr;
    int caseNum;
};

// helper functions
command processCommand(string ans);
void helpMenu();
void load(list <BST> &closet, command cmd);
int toInt(string val);
bool commandSwitch(list <BST> &closet, command cmd);
bool exit();
void invalidCommand();

// stl list functions
void insertItem(list <BST> &closet, string i, int c, string l);
void removeItem(list <BST> &closet, string i);
void removeItemFrom(list <BST> &closet, string i, string l);
void findItem(list <BST> &closet, string i);
void findItemIn(list <BST> &closet, string i, string l);
void createContainer(list <BST> &closet, string l);
void destroyContainer(list <BST> &closet, string l);
void displayIn(list <BST> &closet, string l);
void displayPre(list <BST> &closet, string l);
void displayPost(list <BST> &closet, string l);


int main() {
    list <BST> closet;
    
    cout << "Enter 'help' to see a list of commands." << endl;

    bool exitLoop = false;
    while(!exitLoop) {
        // take user answer thru call to getline to allow for easier processing
        string ans;
        getline(cin, ans);

        // parses command and returns appropriate switch case value
        command cmd = processCommand(ans);

        exitLoop = commandSwitch(closet, cmd);
        cin.clear();
    }
    // if loop is exited, program terminates
    return 0;
}

// command switch
bool commandSwitch(list <BST> &closet, command cmd) {
    switch (cmd.caseNum) {
        // help menu
        case 1: { helpMenu(); cout << endl; break; }
            
        // insert <item> <count> into <container>
        case 2: { insertItem(closet, cmd.cmdArr[0], toInt(cmd.cmdArr[1]), cmd.cmdArr[3]); cout << endl; break; }
            
        // remove <item> from <container>
        case 3: { removeItemFrom(closet, cmd.cmdArr[0], cmd.cmdArr[2]); cout << endl; break; }
        
        // remove <item>
        case 4: { removeItem(closet, cmd.cmdArr[0]); cout << endl; break; }

        // find <item> in <container>
        case 5: { findItemIn(closet, cmd.cmdArr[0], cmd.cmdArr[2]); cout << endl; break; }

        // find <item>
        case 6: { findItem(closet, cmd.cmdArr[0]); cout << endl; break; }

        // display <container> in
        case 7: { displayIn(closet, cmd.cmdArr[0]); cout << endl; break; }

        // display <container> pre
        case 8: { displayPre(closet, cmd.cmdArr[0]); cout << endl; break; }
            
        // display <container> post
        case 9: { displayPost(closet, cmd.cmdArr[0]); cout << endl; break; }
            
        // load <file>
        case 10: { load(closet, cmd); cout << endl; break; }
            
        // create <container>
        case 11: { createContainer(closet, cmd.cmdArr[0]); cout << endl; break; }
            
        // destroy <container>
        case 12: { destroyContainer(closet, cmd.cmdArr[0]); cout << endl; break; }

        // exit
        case 13: { return exit(); break; }
            
        // invalid command
        case 14: { invalidCommand(); cout << endl; break; }
    }
    return false;
}


// string processing
command processCommand(string ans) {
    command returnCmd;
    string cmd;
    stringstream ss(ans);
    getline(ss, cmd, ' ');
    
    int SIZE = 5;
    string cmdParam;
    returnCmd.cmdArr = new string[SIZE];
    int i = 0;
    while (ss >> cmdParam)
    {
        returnCmd.cmdArr[i] = cmdParam;
        i++;
    }
        
    if (cmd == "help") {
        returnCmd.caseNum = 1;
        return returnCmd;
    } else if (cmd == "insert") {
        returnCmd.caseNum = 2;
        return returnCmd;
    } else if (cmd == "remove") {
        if (returnCmd.cmdArr[1] == "from") {
            returnCmd.caseNum = 3;
            return returnCmd;
        } else {
            returnCmd.caseNum = 4;
            return returnCmd;
        }
    } else if (cmd == "find") {
        if (returnCmd.cmdArr[1] == "in") {
            returnCmd.caseNum = 5;
            return returnCmd;
        } else {
            returnCmd.caseNum = 6;
            return returnCmd;
        }
    } else if (cmd == "display") {
        if (returnCmd.cmdArr[1] == "in") {
            returnCmd.caseNum = 7;
            return returnCmd;
        } else if (returnCmd.cmdArr[1] == "pre") {
            returnCmd.caseNum = 8;
            return returnCmd;
        } else if (returnCmd.cmdArr[1] == "post") {
            returnCmd.caseNum = 9;
            return returnCmd;
        } else {
            // invalid
            returnCmd.caseNum = 14;
            return returnCmd;
        }
    } else if (cmd == "load") {
        returnCmd.caseNum = 10;
        return returnCmd;
    } else if (cmd == "create") {
        returnCmd.caseNum = 11;
        return returnCmd;
    } else if (cmd == "destroy") {
        returnCmd.caseNum = 12;
        return returnCmd;
    } else if (cmd == "exit") {
           returnCmd.caseNum = 13;
           return returnCmd;
    } else {
        returnCmd.caseNum = 14;
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
    cout << "1 : insert <item> <count> into <container> - Inserts count of the specified item into the given container." << endl;
    cout << "2 : remove <item> from <container> -  Removes the specified item from the given container." << endl;
    cout << "3 : remove <item> - Removes the specified item from each container." << endl;
    cout << "4 : find <item> in <container> - Searches the given container for the specified item, displaying the item name and item count if it is found." << endl;
    cout << "5 : find <item> - Searches each container for the specified item, displaying the container name, item name, and item count each time it is found." << endl;
    cout << "6 : display <container> in - Displays the contents of the specified container in order." << endl;
    cout << "7 : display <container> pre - Displays the contents of the specified container pre order." << endl;
    cout << "8 : display <container> post - Displays the contents of the specified container post order." << endl;
    cout << "9 : load <file> - Parses the contents of a file as if they were entered from the command line." << endl;
    cout << "11: create <container> - Creates the specified container and adds it to the list of containers." << endl;
    cout << "12: destroy <container> -  Destroys the specified container and its contents." << endl;
    cout << "13: exit - Exits program." << endl;
}

void invalidCommand() { cout << endl << "Please enter a valid command." << endl; }

void load(list <BST> &closet, command cmd) {
    string filePath = cmd.cmdArr[0];
    ifstream inFile(filePath);
    if (inFile) {
        string line;
        while(getline(inFile, line)) {
            command loadedCmd = processCommand(line);
            cout << "Executing: '" << line << "'" << endl;

            commandSwitch(closet, loadedCmd);
        }
    } else {
        cout << endl << "Invalid file path. Please try again." << endl << endl;
    }
}

bool exit() {
    cout << endl <<  "Exiting... Goodbye :)" << endl;
    return true;
}

// stl list functions
void insertItem(list <BST> &closet, string i, int c, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->insert(i, c);
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
}

void removeItem(list <BST> &closet, string i) {
    list <BST>::iterator it;
    
    for (it = closet.begin(); it != closet.end(); ++it) {
        it->remove(i);
    }
}

void removeItemFrom(list <BST> &closet, string i, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->remove(i);
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
       }
        advance(it, 1);
    }
}

void findItem(list <BST> &closet, string i) {
    list <BST>::iterator it;
    
    for (it = closet.begin(); it != closet.end(); ++it) {
        cout << "Container: " << it->location << endl;
        it->search(i);
        cout << endl;
    }
}

void findItemIn(list <BST> &closet, string i, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->search(i);
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
}

void createContainer(list <BST> &closet, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            cout << endl << "Container already exists!" << endl;
            found = true;
        } else if (it == closet.end()) {
            closet.push_back(BST(l));
            return;
        }
        advance(it, 1);
    }
}

void destroyContainer(list <BST> &closet, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            closet.erase(it);
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
}

void displayIn(list <BST> &closet, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->inOrder();
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
    if (found) { cout << endl; }
}

void displayPre(list <BST> &closet, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->preOrder();
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
    if (found) { cout << endl; }
}

void displayPost(list <BST> &closet, string l) {
    list <BST>::iterator it = closet.begin();
    
    bool found = false;
    while (!found) {
        if (it->location == l) {
            it->postOrder();
            found = true;
        } else if (it == closet.end()) {
            cout << endl << "Container not found!" << endl;
            return;
        }
        advance(it, 1);
    }
    if (found) { cout << endl; }
}

