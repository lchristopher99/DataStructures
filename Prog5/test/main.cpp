//
//  main.cpp
//  test
//
//  Created by Logan Christopher on 2/17/20.
//  Copyright © 2020 Logan Christopher. All rights reserved.
//
#include <iostream>
using namespace std;

template <class T>
T getIdx(T a[], T b) {
    int i = 0;
    while (i < 7) {
        if (a[i] == b) {
            return i;
        }
        i++;
    }
    
    return -1;
}

int main () {
    int arr[6] = {1,2,3,4,5,6};
    int b = 11;
    int result;
    
    result = getIdx<int>(arr, b);
    cout << result << endl;
    
    return 0;
}
