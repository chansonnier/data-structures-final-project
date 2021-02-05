#include "hashquad.hpp"
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
  int i = hashFunction(key); // ex. hashFunction(40009) = 1
  int quadInsert = 1;
  bool inserted = 0;            // to check whether insertion finished or not
  if (table[i] == -1){
    table[i] = key;             // it was empty/available
    return 1;                   // 1 = insert w/out collision(s)
  }
  else if (table[i] != -1){
    while (!inserted){
      while ((!inserted) && ((i + (quadInsert * quadInsert)) < tableSize)){ // while not inserted yet & avoiding a seg fault
        if (table[i+(quadInsert * quadInsert)] == -1){           // that's an empty slot in the table
          inserted = true;      // this will break the loop
        }
        else {
          quadInsert++;
          numOfInsertCollisions++;    // then there was a collision, so ++ (Prof Ashraf said in the interview to count each of these as a collision)
        }
      }
      if ((i + (quadInsert * quadInsert)) >= tableSize){
        i = (i+ (quadInsert*quadInsert)) % tableSize; // get i back to indexing within the table's size / avoid a seg fault
      }
    }
    table[i+(quadInsert * quadInsert)] = key; // empty slot found eventually, so insert the key here
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
  int quadSearch = 1;
  bool found = 0;               // to check whether search finished or not
  if (table[i] == key){
    return 1;                         // then it was found without a collision
  }
  else if (table[i] != key){
    while (!found){
      while ((!found) && ((i + (quadSearch * quadSearch)) < tableSize)){ // while not found yet & avoiding a seg fault
        if (table[i+(quadSearch * quadSearch)] == key){ // then done
          found = true;      // this will break the loop
          return 2;             // found but with collision(s)
        }
        else {
          quadSearch++;
          numOfSearchCollisions++;    // then there was a collision, so ++ (Prof Ashraf said in the interview to count each of these as a collision)
        }
      }
      if ((i + (quadSearch * quadSearch)) >= tableSize){
        i = (i+ (quadSearch*quadSearch)) % tableSize; // get i back to indexing within the table's size / avoid a seg fault
      }
    }
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
