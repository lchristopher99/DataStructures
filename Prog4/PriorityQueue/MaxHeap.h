/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: xcode using g++
 Program Description:
 Program Description: This program utilizes priority queue in order to simulate an ER.
 */

#ifndef MaxHeap_h
#define MaxHeap_h

#include <string>
#include <iostream>
#include "patient.h"
using namespace std;

// helpers
void swap(patient *x, patient *y);
int priorityLevel(string l);
  
class MaxHeap {
public:
    patient *heapArr;
    int maxSize;
    int currSize;
    MaxHeap(int maxSize);
    void insertPatient(patient p);
    patient removeMax();
    void MaxHeapify(int i);
    
    // helpers
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    patient getMax() { return heapArr[0]; }
    int getCurrSize() { return currSize; }
};
  
MaxHeap::MaxHeap(int max) {
    currSize = 0;
    maxSize = max;
    heapArr = new patient[max];
}
  
void MaxHeap::insertPatient(patient k) {
    if (currSize == maxSize) {
        cout << endl << "Could not insert... Current size exceeds max size..." << endl;
        return;
    }
  
    // insert at end
    currSize++;
    int i = currSize - 1;
    heapArr[i] = k;
  
    // Fix max heap property if necessary
    while (i != 0 && priorityLevel(heapArr[parent(i)].priority) < priorityLevel(heapArr[i].priority)) {
       swap(&heapArr[i], &heapArr[parent(i)]);
       i = parent(i);
    }
}
  
patient MaxHeap::removeMax() {
    if (currSize <= 0) {
        cout << endl << "Could not remove... Current size is 0..." << endl;
        // returns empty patient log
        return patient();
    }
    
    if (currSize == 1) {
        currSize--;
        return heapArr[0];
    }
  
    // Store max value, remove it from heap
    patient root = heapArr[0];
    heapArr[0] = heapArr[currSize-1];
    currSize--;
    MaxHeapify(0);
  
    return root;
}

void MaxHeap::MaxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < currSize && priorityLevel(heapArr[l].priority) > priorityLevel(heapArr[i].priority)) { largest = l; }
    if (l < currSize && priorityLevel(heapArr[l].priority) == priorityLevel(heapArr[i].priority) && heapArr[l].TicketNum < heapArr[i].TicketNum) { largest = l; }
    if (r < currSize && priorityLevel(heapArr[r].priority) > priorityLevel(heapArr[largest].priority)) { largest = r; }
    if (r < currSize && priorityLevel(heapArr[r].priority) == priorityLevel(heapArr[largest].priority) && heapArr[r].TicketNum < heapArr[largest].TicketNum) { largest = r; }
    if (largest != i) {
        swap(&heapArr[i], &heapArr[largest]);
        MaxHeapify(largest);
    }
}

void swap(patient *x, patient *y) {
    patient temp = *x;
    *x = *y;
    *y = temp;
}

int priorityLevel(string l) {
    if (l == "ambulatory") {
        return 1;
    } else if (l == "non-urgent") {
        return 2;
    } else if (l == "urgent") {
        return 3;
    } else if (l == "critical") {
        return 4;
    } else if (l == "code") {
        return 5;
    }
    return 1;
}

#endif /* MaxHeap_h */
