/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list in order to visualize an adjacency matrix/list
*/

#ifndef AdjMatrix_h
#define AdjMatrix_h

#include "dubLinkedList.h"
#include "vertex.h"
#include <string>
#include <iostream>
using namespace std;

// doubly linked list class
class AdjMatrix {
private:
    DubLinkedList vertList;
    int vertArr[20][20];
    
public:
    // contructor
    AdjMatrix() {};
    
    // methods
    void add(int v);
    void addEdge(int i, int f, int w);
    void removeVert(int v);
    void removeEdge(int i, int f);
    void findEdge(int i, int f);
    void displayMatrix();
    void displayVert();
    void displayList();
    void output(string path);
};

void AdjMatrix::add(int v) { vertList.insert(new Vertex(v)); }

void AdjMatrix::removeVert(int v) { vertList.remove(Vertex(v)); }

void AdjMatrix::displayVert() { vertList.displayVert(); }

void AdjMatrix::displayMatrix() { vertList.displayMatrix(vertArr); }

void AdjMatrix::displayList() { vertList.displayList(); }

void AdjMatrix::output(string path) { vertList.outputMatrix(vertArr, path); }

void AdjMatrix::addEdge(int i, int f, int w) {
    if (vertList.doesExist(Vertex(i)) && vertList.doesExist(Vertex(f))) {
        Vertex *tempInitial = vertList.find(Vertex(i));
        Vertex *tempFinal = new Vertex(f);
        while (tempInitial->adjVert != nullptr) {
            tempInitial = tempInitial->adjVert;
        }
        tempInitial->adjVert = tempFinal;
        tempInitial->adjVert->cost = w;
    }
}

void AdjMatrix::findEdge(int i, int f) {
    if (vertList.doesExist(Vertex(i)) && vertList.doesExist(Vertex(f))) {
        if (vertList.find(Vertex(i))->adjVert->getValue() == f) {
            cout << endl << "Found Edge: " << i << " to " << f << " with weight of " << vertList.find(Vertex(i))->adjVert->getCost() << endl;
        } else {
            cout << endl << "Edge not found!" << endl;
        }
    }
}

void AdjMatrix::removeEdge(int i, int f) {
    if (vertList.find(Vertex(i))->adjVert != NULL) {
        if (vertList.find(Vertex(i))->adjVert->getValue() == f) {
            vertList.find(Vertex(i))->adjVert = NULL;
        } else {
            cout << endl << "Edge not found!" << endl;
        }
    } else {
        cout << endl << "Edge not found!" << endl;
    }
}

#endif /* AdjMatrix_h */
