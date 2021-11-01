/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list in order to visualize an adjacency matrix/list
*/

#ifndef vertex_h
#define vertex_h

#include <string>
#include "dubLinkedList.h"
using namespace std;

struct Vertex {
    int value;
    int cost;
    Vertex *adjVert;
    Vertex(): value(NULL), cost(NULL), adjVert(nullptr) {}
    Vertex(int v): value(v), cost(NULL), adjVert(nullptr) {}
    Vertex(int v, int c): value(v), cost(c), adjVert(nullptr) {}
    
    int getValue() { return value; }
    int getCost() { return cost; }
    Vertex* getAdjVert() { return adjVert; }
};

#endif /* vertex_h */
