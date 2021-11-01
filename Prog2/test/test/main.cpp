#include "adjMatrix.h"
#include "adjList.h"
#include <iostream>
using namespace std;

int main() {
    int v = 3; // num of vertices
    
    AdjMatrix matrix;
    matrix.add_edge(1, 2, 5);
    matrix.add_edge(0, 2, 6);
    matrix.add_edge(1, 0, 7);
    matrix.displayMatrix(v);
    
    cout << endl;
    
    AdjList list(v);
    list.add_edge(0, 1);
    list.add_edge(0, 2);
    list.add_edge(1, 2);
    list.add_edge(2, 3);
    list.displayList(v);
}
