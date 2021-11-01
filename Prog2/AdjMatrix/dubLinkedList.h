/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list in order to visualize an adjacency matrix/list
*/

#ifndef dubLinkedList_h
#define dubLinkedList_h

#include "vertex.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// node class
class Node {
private:
    Vertex *v;
    
public:
    Node(Vertex *v): v(v), nextNode(NULL), prevNode(NULL) {}
    Node* nextNode;
    Node* prevNode;
    
    int getValue() { return v->getValue(); }
    Vertex *getVert() { return v; }
    //void setVert(Vertex *v) { v->adjVert = v; }
};

// doubly linked list class
class DubLinkedList {
private:
    Node *head;
    Node *tail;
    
public:
    // contructor
    DubLinkedList(): head(NULL), tail(NULL) {}
    
    // methods
    void insert(Vertex *v);
    void remove(Vertex v);
    Vertex* find(Vertex v);
    bool doesExist(Vertex v);
    void displayVert();
    void displayList();
    void displayMatrix(int arr[][20]);
    int getNumNodes();
    void outputMatrix(int arr[][20], string p);
};

void DubLinkedList::outputMatrix(int arr[][20], string p) {
    ofstream outFile;
    outFile.open(p);
    int numV = getNumNodes();
    Node *ptr = head;
    
    if (numV == 0) {
        cout << endl << "Matrix is Empty!" << endl;
    } else {
        // add edges to matrix based off updated adj list (dubLinkedList)
        while(ptr != NULL) {
            Vertex *tempVert = ptr->getVert();
            while(tempVert->getAdjVert() != nullptr) {
                int u = tempVert->getValue();
                int v = tempVert->adjVert->getValue();
                int w = tempVert->adjVert->getCost();

                arr[u-1][v-1] = w;

                tempVert = tempVert->adjVert;
            }
            ptr = ptr->nextNode;
        }
        
        // display
        int i, j;
        for(i = 0; i < numV; i++) {
             for(j = 0; j < numV; j++) {
                outFile << arr[i][j] << " ";
             }
             outFile << endl;
        }
    }
    
    outFile << endl;
    ptr = head;
    
    if (!ptr) {
        cout << endl << "List is empty!" << endl;
    } else {
        while(ptr != NULL) {
            outFile << ptr->getValue();
            Vertex *tempVert = ptr->getVert();
            while(tempVert->getAdjVert() != nullptr) {
                outFile << " " << tempVert->adjVert->getValue() << ":" << tempVert->adjVert->getCost();
                tempVert = tempVert->adjVert;
            }
            outFile << endl;
            ptr = ptr->nextNode;
        }
    }
    
    outFile.close();
}

void DubLinkedList::insert(Vertex *v) {
    if (getNumNodes() <= 20) {
        Node *newNode = new Node(v);
        Node *tempNode = head;
        
        if (head != NULL) {
            tail = newNode;
            while(tempNode->nextNode != NULL) {
                tempNode = tempNode->nextNode;
            }
            tempNode->nextNode = tail;
            tail->prevNode = tempNode;
        } else {
            head = newNode;
        }
    } else {
        cout << endl << "List cannot contain more than 20 vertices... Remove a vertex and try again." << endl;
    }
}

// vertex list
void DubLinkedList::displayVert() {
    Node *ptr = head;
    
    if (!ptr) {
        cout << endl << "List is empty!" << endl;
    } else {
        cout << endl << "Vertex List:" << endl;
        cout << "-------------------------------" << endl;
        while(ptr != NULL) {
            cout << ptr->getValue() << endl;
            ptr = ptr->nextNode;
        }
    }
}

// adj list
void DubLinkedList::displayList() {
    Node *ptr = head;
    
    if (!ptr) {
        cout << endl << "List is empty!" << endl;
    } else {
        cout << endl << "Adjacency List:" << endl;
        cout << "-------------------------------" << endl;
        while(ptr != NULL) {
            cout << ptr->getValue();
            Vertex *tempVert = ptr->getVert();
            while(tempVert->getAdjVert() != nullptr) {
                cout << " " << tempVert->adjVert->getValue() << ":" << tempVert->adjVert->getCost();
                tempVert = tempVert->adjVert;
            }
            cout << endl;
            ptr = ptr->nextNode;
        }
    }
}

// adj matrix
void DubLinkedList::displayMatrix(int arr[][20]) {
    int numV = getNumNodes();
    
    if (numV == 0) {
        cout << endl << "Matrix is Empty!" << endl;
    } else {
        Node *ptr = head;
        
        // add edges to matrix based off updated adj list (dubLinkedList)
        while(ptr != NULL) {
            Vertex *tempVert = ptr->getVert();
            while(tempVert->getAdjVert() != nullptr) {
                int u = tempVert->getValue();
                int v = tempVert->adjVert->getValue();
                int w = tempVert->adjVert->getCost();
                
                arr[u-1][v-1] = w;
                
                tempVert = tempVert->adjVert;
            }
            ptr = ptr->nextNode;
        }
        
        // display
        cout << endl << "Adjacency Matrix:" << endl;
        cout << "-------------------------------" << endl;
        int i, j;
        for(i = 0; i < numV; i++) {
             for(j = 0; j < numV; j++) {
                cout << arr[i][j] << " ";
             }
             cout << endl;
        }
    }
}

int DubLinkedList::getNumNodes() {
    Node *ptr = head;
    int cnt = 0;
    
    if (!ptr) {
        return 0;
    } else {
        while(ptr != NULL) {
            cnt += 1;
            ptr = ptr->nextNode;
        }
    }
    return cnt;
}

Vertex* DubLinkedList::find(Vertex v) {
    Node *ptr = head;
    
    while(ptr != NULL) {
        if (ptr->getValue() == v.value) {
            //cout << ptr->getValue() << endl;
            return ptr->getVert();
        }
        ptr = ptr->nextNode;
    }
    cout << endl <<  "Vertex " << v.value << " does not exist." << endl;
    return nullptr;
}

bool DubLinkedList::doesExist(Vertex v) {
    Node *ptr = head;
    
    while(ptr != NULL) {
        if (ptr->getValue() == v.value) {
            //cout << ptr->getValue() << endl;
            return true;
        }
        ptr = ptr->nextNode;
    }
    cout << endl << "Vertex " << v.value << " does not exist." << endl;
    return false;
}

void DubLinkedList::remove(Vertex v) {
    Node *ptr = head;
    Node *ptr2;
    Node *ptr3;
    
    while(ptr != NULL) {
        if (ptr->getValue() == v.value) {
            ptr2 = ptr->nextNode;
            ptr3 = ptr->prevNode;
            if (ptr2) {
                if (!ptr3) {
                    head = ptr2;
                    ptr2->prevNode = NULL;
                } else {
                    ptr3->nextNode = ptr2;
                    ptr2->prevNode = ptr3;
                }
            } else {
                if (!ptr3) {
                    head = NULL;
                    tail = NULL;
                } else {
                    tail = ptr3;
                    ptr3->nextNode = NULL;
                }
            }
            
            delete ptr;
            return;
        }
        ptr = ptr->nextNode;
    }
    cout << "Vertex " << v.value << " does not exist." << endl << endl;
}

#endif /* dubLinkedList_h */
