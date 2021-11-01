/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list in order to visualize an adjacency matrix/list
*/

#include "AdjMatrix.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

struct command {
    string *cmdArr;
    int caseNum;
};

// helper functions
command processCommand(string ans);
void helpMenu();
void load(AdjMatrix &matrix, command cmd);
int toInt(string val);
bool commandSwitch(AdjMatrix &matrix, command cmd);
bool exit();
void invalidCommand();

int main() {
    AdjMatrix matrix;
    
    cout << "Enter 'help' to see a list of commands." << endl;

    bool exitLoop = false;
    while(!exitLoop) {
        // take user answer thru call to getline to allow for easier processing
        string ans;
        getline(cin, ans);

        // parses command and returns appropriate switch case value
        command cmd = processCommand(ans);

        exitLoop = commandSwitch(matrix, cmd);
        cin.clear();
    }
    // if loop is exited, program terminates
    return 0;
}

// command switch
bool commandSwitch(AdjMatrix &matrix, command cmd) {
    switch (cmd.caseNum) {
        // help menu
        case 1: { helpMenu(); cout << endl; break; }
            
        // add <vertex>
        case 2: { matrix.add(toInt(cmd.cmdArr[0])); cout << endl; break; }
            
        // add <initial> to <final> weight <weight>
        case 3: { matrix.addEdge(toInt(cmd.cmdArr[0]), toInt(cmd.cmdArr[2]), toInt(cmd.cmdArr[4])); cout << endl; break; }
        
        // remove <initial> to <final>
        case 4: { matrix.removeEdge(toInt(cmd.cmdArr[0]), toInt(cmd.cmdArr[2])); cout << endl; break; }

        // remove <vertex>
        case 5: { matrix.removeVert(toInt(cmd.cmdArr[0])); cout << endl; break; }

        // find <initial> to <final>
        case 6: { matrix.findEdge(toInt(cmd.cmdArr[0]), toInt(cmd.cmdArr[2])); cout << endl; break; }

        // display matrix
        case 7: { matrix.displayMatrix(); cout << endl; break; }

        // display vertices
        case 8: { matrix.displayVert(); cout << endl; break; }
            
        // display list
        case 9: { matrix.displayList(); cout << endl; break; }
            
        // load <file>
        case 10: { load(matrix, cmd); cout << endl; break; }
            
        // output
        case 11: { matrix.output(cmd.cmdArr[0]); cout << endl; break; }

        // exit
        case 12: { return exit(); break; }
            
        // invalid command
        case 13: { invalidCommand(); cout << endl; break; }
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
    string cmdArr[SIZE];
    int i = 0;
    while (ss >> cmdParam)
    {
        cmdArr[i] = cmdParam;
        i++;
    }
    
    returnCmd.cmdArr = new string[SIZE];
    i = 0;
    while(i < SIZE) {
        returnCmd.cmdArr[i] = cmdArr[i];
        i++;
    }
        
    if (cmd == "help") {
        returnCmd.caseNum = 1;
        return returnCmd;
    } else if (cmd == "add") {
        if (cmdArr[1] == "to") {
            returnCmd.caseNum = 3;
            return returnCmd;
        } else {
            returnCmd.caseNum = 2;
            return returnCmd;
        }
    } else if (cmd == "remove") {
        if (cmdArr[1] == "to") {
            returnCmd.caseNum = 4;
            return returnCmd;
        } else {
            returnCmd.caseNum = 5;
            return returnCmd;
        }
    } else if (cmd == "find") {
        returnCmd.caseNum = 6;
        return returnCmd;
    } else if (cmd == "display") {
        if (cmdArr[0] == "matrix") {
            returnCmd.caseNum = 7;
            return returnCmd;
        } else if (cmdArr[0] == "vertices") {
            returnCmd.caseNum = 8;
            return returnCmd;
        } else if (cmdArr[0] == "list") {
            returnCmd.caseNum = 9;
            return returnCmd;
        } else {
            // invalid
            returnCmd.caseNum = 13;
            return returnCmd;
        }
    } else if (cmd == "load") {
        returnCmd.caseNum = 10;
        return returnCmd;
    } else if (cmd == "output") {
        returnCmd.caseNum = 11;
        return returnCmd;
    } else if (cmd == "exit") {
        returnCmd.caseNum = 12;
        return returnCmd;
    } else {
        returnCmd.caseNum = 13;
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
    cout << "1 : add <vertex> - Adds the specified vertex to the vertex list." << endl;
    cout << "2 : add <initial> to <final> weight <weight> - Add an edge with the specified weight from the specified initial vertex to the specified final vertex." << endl;
    cout << "3 : remove <vertex> - Removes the specified vertex and all edges to or from that vertex." << endl;
    cout << "4 : remove <initial> to <final> - Removes the edge with the specified initial vertex and the specified final vertex." << endl;
    cout << "5 : find <initial> to <final> - Finds the edge with the specified initial vertex to the specified final vertex and displays its weight." << endl;
    cout << "6 : display matrix - Displays current adjancency matrix." << endl;
    cout << "7 : display vertices - Displays current vertex list." << endl;
    cout << "8 : display list - Displays current adjacency list." << endl;
    cout << "9 : load <file> - Parses the contents of a file as if they were entered from the command line." << endl;
    cout << "10: exit - Exits program." << endl;
}

void invalidCommand() { cout << endl << "Please enter a valid command." << endl; }

void load(AdjMatrix &matrix, command cmd) {
    string filePath = cmd.cmdArr[0];
    ifstream inFile(filePath);
    if (inFile) {
        string line;
        while(getline(inFile, line)) {
            command loadedCmd = processCommand(line);
            cout << "Executing: '" << line << "'" << endl;
            
            commandSwitch(matrix, loadedCmd);
        }
    } else {
        cout << endl << "Invalid file path. Please try again." << endl << endl;
    }
}

bool exit() {
    cout << endl <<  "Exiting... Goodbye :)" << endl;
    return true;
}

