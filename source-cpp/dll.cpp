#include "dll.hpp"
#include <iostream>

using namespace std;

DLL::DLL(){}; // default constructor

void DLL::insert(int input){
  // create a new node in heap memory
  Node* nn = new Node;
  nn->key = input;
  nn->next = nullptr;
  nn->prev = nullptr;

  if (head == nullptr){
    head = nn;
    return; // we're done inserting
  }
  else {
    head->prev = nn; // put the new node at the beginning of the list
    nn->next = head; // make the inserted item point to the current head as its 'next'
    head = nn;       // assign the inserted item to head
  }
}

// modified version of above for use in hashchain (returns int instead of void)
int DLL::insert2(int input){
  // create a new node in heap memory
  Node* nn = new Node;
  nn->key = input;
  nn->next = nullptr;
  nn->prev = nullptr;

  if (head != nullptr){
    head->prev = nn; // put the new node at the beginning of the list
    nn->next = head; // make the inserted item point to the current head as its 'next'
    head = nn;       // assign the inserted item to head
    return 2;        // 2 says to the hashchain class that there was a collisions as evidenced by the DLL not being empty here
  }
  else if (head == nullptr){
    head = nn;
    return 1; // we're done inserting, and for the hashchain class's purposes, there was no collision
  }
  else {
    return 0; // some kind of error happened
  }
}


Node* DLL::search(int key){
  Node* temp = head;

  // starting at the head, go from one node to the next until we find the input key
  while (temp->key != key){
    temp = temp->next;
  }

  if (temp->key == key){
    return temp;
  }
  else {
    return nullptr;
  }
}


// modified version of above (returns int instead of Node*)
int DLL::search2(int key){
  Node* temp = head;
  bool collision = 0;           // if there are any collisions this will be changed to 1

  // starting at the head, go from one node to the next until we find the input key
  if (temp->key != key){ 
    temp = temp->next;
    collision = 1;              // only need to do this once so this if statement is separate from the otherwise identical while loop just below it
  }
  while (temp->key != key){
    temp = temp->next;          // keep moving to the next node in the DLL until we find the key
  }
  if (( temp->key == key ) && (collision == 0)){
    return 1;
  }
  else if (( temp->key == key ) && (collision == 1)){
    return 2;
  }
  else {
    return 0;                   // not found, and no collisions, naturally
  }
}

void DLL::display(){  // what does the PDF mean by 'display'? Should it just print all nodes' keys?
  Node* temp = head;

  // starting at head, print all nodes' keys
  while (temp != nullptr){
    cout << temp->key << endl;
    temp = temp->next;
  }
}
