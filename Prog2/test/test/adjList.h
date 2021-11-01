//
//  adjList.h
//  test
//
//  Created by Logan Christopher on 2/17/20.
//  Copyright © 2020 Logan Christopher. All rights reserved.
//

#ifndef adjList_h
#define adjList_h

#include <iostream>
#include <list>
using namespace std;
 
class AdjList {
private:
    int numVertices;
    list<int> *adjLists;
    
public:
    AdjList(int numVert);
    void add_edge(int i, int f);
    void displayList(int v);
};
 
AdjList::AdjList(int numVert) {
    numVertices = numVert;
    adjLists = new list<int>[numVert];
}
 
void AdjList::add_edge(int i, int f) {
    adjLists[i].push_front(f);
}

void AdjList::displayList(int v) {
    cout << "Adj List:" << endl;
    for (list<int>::iterator it = adjLists->begin(); it != adjLists->end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
}

#endif /* adjList_h */
