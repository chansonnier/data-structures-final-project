#ifndef HASHCHAIN_HPP
#define HASHCHAIN_HPP

#include "dll.hpp"

struct node
{
  int key;
  struct node* next;
};


class HashTable{

private:
  static const int tableSize = 40009;
  DLL table[tableSize]; //using my DLL class for a table of doubly-linked lists
  int numOfSearchCollisions = 0;
  int numOfInsertCollisions = 0;

public:
  HashTable();

  int insertItem(int key);
  int searchItem(int key);

  // hash function to map values to key
  unsigned int hashFunction(int key);

  void printTable();

  int getNumOfSearchCollisions();
  int getNumOfInsertCollisions();
  int setNumOfSearchCollisions(int input);
  int setNumOfInsertCollisions(int input);
  void resetNumOfSearchCollisions();
  void resetNumOfInsertCollisions();
};

#endif
