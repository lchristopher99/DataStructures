/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: gcc and xcode
 Program Description: This program utilizes a doubly linked list to store the UID and security level of users
*/

#ifndef dubLinkedList_h
#define dubLinkedList_h

#include<string>
#include <iostream>
using namespace std;

// user structure for easier insertion
struct user {
    string UID;
    int securityLevel;
};

// node class
class Node {
private:
    string UID;
    int securityLevel;
    
public:
    Node(string UID, int securityLevel): UID(UID), securityLevel(securityLevel), nextNode(NULL), prevNode(NULL) {}
    Node* nextNode;
    Node* prevNode;
    
    // methods
    string getUID() { return UID; }
    int getSecurityLevel() { return securityLevel; }
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
    void insert(user tempUser);
    void insertBefore(user tempUser, string UID2);
    void insertAfter(user tempUser, string UID2);
    void remove(string UID);
    void find(string UID);
    void display();
    void load();
};

void DubLinkedList::insert(user tempUser) {
    Node *newNode = new Node(tempUser.UID, tempUser.securityLevel);
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
}

void DubLinkedList::insertBefore(user tempUser, string UID2) {
    Node *newNode = new Node(tempUser.UID, tempUser.securityLevel);
    Node *ptr = head;
    Node *ptr2;
    
    while(ptr != NULL) {
        if (ptr->getUID() == UID2) {
            ptr2 = ptr->prevNode;
            if (ptr2) {
                ptr2->nextNode = newNode;
                newNode->prevNode = ptr2;
            } else {
                head = newNode;
                newNode->prevNode = NULL;
            }
            
            ptr->prevNode = newNode;
            newNode->nextNode = ptr;
            
            return;
        }
        ptr = ptr->nextNode;
    }
    cout << "User not found!" << endl << endl;
}

void DubLinkedList::insertAfter(user tempUser, string UID2) {
    Node *newNode = new Node(tempUser.UID, tempUser.securityLevel);
    Node *ptr = head;
    Node *ptr2;
    
    while(ptr != NULL) {
        if (ptr->getUID() == UID2) {
            ptr2 = ptr->nextNode;
            if (ptr2) {
                ptr2->prevNode = newNode;
                newNode->nextNode = ptr2;
            } else {
                newNode->nextNode = NULL;
                tail = newNode;
            }
            
            ptr->nextNode = newNode;
            newNode->prevNode = ptr;
            
            return;
        }
        ptr = ptr->nextNode;
    }
    cout << "User not found!" << endl << endl;
}

void DubLinkedList::display() {
    Node *ptr = head;
    
    if (!ptr) {
        cout << endl << "List is empty!" << endl << endl;
    } else {
        cout << endl << "User Information List:" << endl;
        cout << "-------------------------------" << endl;
        while(ptr != NULL) {
            cout << "UID: " << ptr->getUID() << " SecurityLevel: " << ptr->getSecurityLevel() << endl;
            ptr = ptr->nextNode;
        }
        cout << endl;
    }
    
    
}

void DubLinkedList::find(string UID) {
    Node *ptr = head;
    
    cout << endl;
    while(ptr != NULL) {
        if (ptr->getUID() == UID) {
            cout << "User '" << ptr->getUID() << "' security level is: " << ptr->getSecurityLevel() << endl << endl;
            return;
        }
        ptr = ptr->nextNode;
    }
    cout << "User not found!" << endl << endl;
}

void DubLinkedList::remove(string UID) {
    Node *ptr = head;
    Node *ptr2;
    Node *ptr3;
    
    while(ptr != NULL) {
        if (ptr->getUID() == UID) {
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
    cout << "User not found!" << endl << endl;
}

#endif /* dubLinkedList_h */
