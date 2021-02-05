#include "hashchain.hpp"
#include <iostream>

using namespace std;

HashTable::HashTable(){}; // default constructor

unsigned int HashTable::hashFunction(int key){
  return key % tableSize;
}


int HashTable::insertItem(int key){
  int i = hashFunction(key); // ex. hashFunction(400009) = 1
  int insertResult = table[i].insert2(key);      // ex. table[1].insert2(400009) calls the DLL member function .insert2() with the input key
  if (insertResult == 1){
    return 1;                         // then it was inserted without a collision
  }
  if (insertResult == 2){
    numOfInsertCollisions++;          // then it was inserted, but with a collision, so do ++
    return 1; // found
  }
  return 0;                           // error inserting
}

void HashTable::printTable(){
  for (int i = 0; i < tableSize; i++){
    table[i].display(); // won't print anything at each index unless there's at least one thing in the bucket there
  }
}

int HashTable::searchItem(int key){
  int i = hashFunction(key);
  int searchResult = table[i].search2(key); // assign the DLL class's search result to this var (table is an arr of DLL objects)
  if (searchResult == 1){
    return 1;                   // then it was found without a collision
  }
  else if (searchResult == 2){
    numOfSearchCollisions++;          // then it was found, but with a collision, so do ++
    return 1; // found
  }
  return 0;
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
