/*
 Student Name: Logan Christopher
 Student NetID: CLC1085
 Compiler Used: xcode using g++
 Program Description:
 Program Description: This program utilizes a BST alongside a STL list in order to organize a closet with mentioned data structures
 */

#ifndef BST_h
#define BST_h

#include<string>
#include<iostream>
#include<fstream>

using namespace std;

struct Node {
    int count;
    string item;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;
    
public:
    BST(): root(NULL) {}
    BST(string l): location(l), root(NULL) {}
    ~BST() { root = deleteNode(root); }
    string location;
    void deleteTree() { root = deleteNode(root); }
    void insert(string x, int y) { root = rInsert(x, y, root); }
    void remove(string x) { root = rRemove(x, root); }
    bool isEmpty() { return(root == NULL); }
    void preOrder() { rPreOrder(root); }
    void inOrder() { rInOrder(root); }
    void postOrder() { rPostOrder(root); }
    int getNumNodes() {
        int i = 0;
        rGetNumNodes(root, i);
        return i;
    }
    void search(string x) {
        if (rSearch(root, x)) {
            cout << rSearch(root, x)->count << " " << rSearch(root, x)->item << "'s" << " exist!" << endl;
        } else {
            cout << x << " : Item does not exist in container!" << endl;
        }
    }
    // main recursive methods
    Node* rInsert(string x, int y, Node* t)
    {
        if(t == NULL) {
            t = new Node;
            t->item = x;
            t->count = y;
            // this fixes ghost node problem
            t->left = t->right = NULL;
        } else if(x < t->item) {
            t->left = rInsert(x, y, t->left);
        } else if(x > t->item) {
             t->right = rInsert(x, y, t->right);
        }
        return t;
    }
    Node* rRemove(string x, Node* t) {
        Node* temp;
        if(t == NULL) {
            return NULL;
        } else if(x < t->item) {
            t->left = rRemove(x, t->left);
        } else if(x > t->item) {
            t->right = rRemove(x, t->right);
        } else if(t->left && t->right) {
            temp = findMin(t->right);
            t->item = temp->item;
            t->right = rRemove(t->item, t->right);
        } else {
            temp = t;
            if(t->left == NULL) {
                t = t->right;
            } else if(t->right == NULL) {
                t = t->left;
            }
            delete temp;
        }
        
        return t;
    }
    Node* rSearch(Node* t, string x) {
        if(t == NULL) {
            return NULL;
        } else if(x < t->item) {
            return rSearch(t->left, x);
        } else if(x > t->item) {
            return rSearch(t->right, x);
        } else {
            return t;
        }
    }
    // traversal methods
    void rInOrder(Node* t) {
        if(t == NULL) return;
        rInOrder(t->left);
        cout << t->item << " " << t->count << ", ";
        rInOrder(t->right);
    }
    void rPreOrder(Node* t) {
        if(t == NULL) return;
        cout << t->item << " " << t->count << ", ";
        rPreOrder(t->left);
        rPreOrder(t->right);
    }
    void rPostOrder(Node* t) {
        if(t == NULL) return;
        rPostOrder(t->left);
        rPostOrder(t->right);
        cout << t->item << " " << t->count << ", ";
    }
    // helper functions
    void rGetNumNodes(Node* t, int &i) {
        if(t == NULL) return;
        rGetNumNodes(t->left, i);
        i += 1;
        rGetNumNodes(t->right, i);
    }
    
    Node* findMin(Node* t)
    {
        if(t == NULL) {
            return NULL;
        } else if(t->left == NULL) {
            return t;
        } else {
            return findMin(t->left);
        }
    }
    Node* findMax(Node* t) {
        if(t == NULL) {
            return NULL;
        } else if(t->right == NULL) {
            return t;
        } else {
            return findMax(t->right);
        }
    }
    // deconstructor function
    Node* deleteNode(Node* t) {
        if(t == NULL) return NULL;
        {
            deleteNode(t->left);
            deleteNode(t->right);
            delete t;
        }
        return NULL;
    }
};

#endif /* BST_h */
