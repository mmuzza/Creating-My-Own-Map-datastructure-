// mymap.h
// Author: Muhammad Muzzammil
// Email: mmuzza3@uic.edu
#pragma once

#include <iostream>
#include <sstream>
#include<vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {

          while(curr != nullptr){
            
            if(curr->isThreaded){
              curr = curr->right;
            }
            else{
    
              if(curr->right == nullptr){
                curr = nullptr;
              }
              else{
                while(curr->right->left != nullptr){
                  curr->right = curr->right->left;
                }
                curr = curr->right;
              }
            }

            return iterator(curr);
        }
      }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
      root = nullptr;
      size = 0;
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {

      this->root = other.root;
      this->size = other.size;
      
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {


        // TODO: write this function.
      


        return *this;  // TODO: Update this return.
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {


        // TODO: write this function.


    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {


        // TODO: write this function.


    }


    void put(keyType key, valueType value) {

      NODE* prev = nullptr;
      NODE* cur = root;

      // search for key, return if found
      while(cur != nullptr)
      {
        if(key == cur->key){ //found
          cur->value = value; // Update value if key already exists
          return;
        }
        if(key < cur->key){ // go left:
          prev = cur;
          cur = cur->left;
        }
        else{ // There is no right pointer in traditional traversal
          if(cur->isThreaded){
            prev = cur;
            cur = nullptr;
          }
          else{
            prev = cur;
            cur = cur->right;
          }
        }
      }

      // If not found, insert where we fell out of the tree:

      NODE *n = new NODE();
      n->key = key;
      n->value = value;
      n->left = nullptr;
      n->right = nullptr;

      if(prev == nullptr){
        root = n;
      }
      else if(key < prev->key){
        prev->left = n;
        n->right = prev;
        n->isThreaded = true;
      }
      else{
        NODE *temp = prev->right;
        prev->right = n;
        n->right = temp;
        
        if(prev->isThreaded){
          prev->isThreaded = false;
          n->isThreaded = true;
        }
      }

      size++; // Update the size as we add a node

      //testing below (DELETE LATER)
      cout << n->key << "  --->  " << n->value;
      if(n->isThreaded && n->right != nullptr){
        cout << "---->  is threaded\n";
      }
      else if(n->right == nullptr){
        cout << "---->  NOT threaded\n";
      }
    }



    bool contains(keyType key) {

      NODE* cur = root;

      while(cur != nullptr){
        if(key == cur->key){
          return true; // Key Found
        }
        else if(key < cur->key){
          cur = cur->left;
        }
        else{
          if (cur->isThreaded){
            cur = nullptr;
          }
          else{
            cur = cur->right;
          }
        }
      }

      return false; // Key Not Found
    }



    valueType get(keyType key) {

      NODE* cur = root;

      while(cur != nullptr){
        if(key == cur->key){
          return cur->value; // Key Found
        }
        else if(key < cur->key){
          cur = cur->left;
        }
        else{
          if (cur->isThreaded){
            cur = nullptr;
          }
          else{
            cur = cur->right;
          }
        }
      }

      return valueType(); // Key Not Found...returning default value
    }



    valueType operator[](keyType key) {

     NODE* prev = nullptr;
     NODE* cur = root;

      // search for key, return if found
      while(cur != nullptr)
      {
        if(key == cur->key){ //found
          return cur->value;
        }
        if(key < cur->key){ // go left:
          prev = cur;
          cur = cur->left;
        }
        else{ // There is no right pointer in traditional traversal
          if(cur->isThreaded){
            prev = cur;
            cur = nullptr;
          }
          else{
            prev = cur;
            cur = cur->right;
          }
        }
      }

      // If not found, insert where we fell out of the tree:

      NODE *n = new NODE();
      n->key = key;
      n->value = valueType();
      n->left = nullptr;
      n->right = nullptr;

      if(prev == nullptr){
        root = n;
      }
      else if(key < prev->key){
        prev->left = n;
        n->right = prev;
        n->isThreaded = true;
      }
      else{
        NODE *temp = prev->right;
        prev->right = n;
        n->right = temp;
        
        if(prev->isThreaded){
          prev->isThreaded = false;
          n->isThreaded = true;
        }
      }

      
      size++; // Update the size as we add a node

      return valueType(); // returning default type if key is not found

    }


    int Size() {
        return size;
    }


    iterator begin() {

      NODE* cur = root;

      while(cur!=nullptr){
        if(cur->left == nullptr){
          return iterator(cur);
        }
        else{
          cur = cur->left;
        }
      }
    }


    iterator end() {
        return iterator(nullptr);
    }


    string toString() {

      NODE* cur = root;
      if(cur == nullptr){
        cur = nullptr;
      }
      while(cur->left != nullptr){
        cur = cur->left;
      }
      
      
      while(cur != nullptr){

        cout << "key: " << cur->key << " value: " << cur->value << endl;

        if(cur->isThreaded){
          cur = cur->right;
        }
        else{

          if(cur->right == nullptr){
            cur = nullptr;
          }
          else{
            while(cur->right->left != nullptr){
              cur->right = cur->right->left;
            }
            cur = cur->right;
          }
        }
      }

      return {};
    }



    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }
};