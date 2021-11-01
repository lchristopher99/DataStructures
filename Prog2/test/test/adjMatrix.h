//
//  adjMatrix.h
//  test
//
//  Created by Logan Christopher on 2/17/20.
//  Copyright © 2020 Logan Christopher. All rights reserved.
//

#ifndef adjMatrix_h
#define adjMatrix_h

#include <iostream>
using namespace std;

class AdjMatrix {
public:
    int vertArr[20][20];
    void displayMatrix(int v);
    void add_edge(int u, int v, int w);
};

void AdjMatrix::displayMatrix(int v) {
    cout << "Adj Matrix:" << endl;
    int i, j;
    for(i = 0; i < v; i++) {
     for(j = 0; j < v; j++) {
        cout << vertArr[i][j] << " ";
     }
     cout << endl;
    }
}

void AdjMatrix::add_edge(int u, int v, int w) {
    vertArr[u][v] = w;
    vertArr[v][u] = w;
}

#endif /* adjMatrix_h */
