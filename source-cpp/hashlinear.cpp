// h_i(x) = (Hash(x) + i) % HashTableSize
// will it be necessary to make the search stop if it loops completely around (i.e., if all buckets are filled)?

#include "hashlinear.hpp"
#include <iostream>

using namespace std;

HashTable::HashTable(){
  for (int i = 0; i < tableSize; i++){
    //initialize all values in the table to -1 to indicate an empty state
    table[i] = -1;
  }
}; // constructor

unsigned int HashTable::hashFunction(int key){
  return key % tableSize;
}


int HashTable::insertItem(int key){
  int i = hashFunction(key);    // ex. hashFunction(40009) = 1
  if (table[i] == -1){
    table[i] = key;             // it was empty/available
    return 1;                   // 1 = insert w/out collision(s)
  }
  else if (table[i] != -1){     // if it's not -1 then it's occupied already
    while (table[i] != -1){     // now search for an empty slot in the table
      if (i == tableSize -1){   // tableSize -1 to avoid seg fault
        i = 0;                  // then start the search for an empty slot back at idx 0
      }
      else {
        i++;
        numOfInsertCollisions++; // counting each of these as a collision as per Prof Ashraf's
      }                          // instruction in interview grading
    }
    table[i] = key;             // empty slot found eventually, so insert the key here
    return 2;                   // inserted, but with collision(s)
  }
  return 0;                     // error inserting
}

void HashTable::printTable(){
  for (int i = 0; i < tableSize; i++){
    if (table[i] != -1){
      cout << i << "th element in hash table: " << table[i] << endl;
    }
  }
}

int HashTable::searchItem(int key){
  int i = hashFunction(key);
  if (table[i] == key){
    return 1;                         // then it was found without a collision
  }
  else if (table[i] != key){
    while (table[i] != key){
      if (i == tableSize - 1){        // tableSize -1 to avoid seg fault
        i = 0;                        // then start the search for an empty slot back at idx 0
      }
      else {
        numOfSearchCollisions++;      // there was a collision, so do ++
        i++;
      }
    }
    if (table[i] == key){
      return 2;                       // found but with collision(s)
    }
  }
  return 0;                           // error / not found
}

int HashTable::getNumOfSearchCollisions(){
  return numOfSearchCollisions;
}

int HashTable::getNumOfInsertCollisions(){
  return numOfInsertCollisions;
}

int HashTable::setNumOfSearchCollisions(int input){
  numOfSearchCollisions = input;
}

int HashTable::setNumOfInsertCollisions(int input){
  numOfInsertCollisions = input;
}

void HashTable::resetNumOfSearchCollisions(){
  numOfSearchCollisions = 0;
}

void HashTable::resetNumOfInsertCollisions(){
  numOfInsertCollisions = 0;
}
