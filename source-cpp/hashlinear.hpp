#ifndef HASHLINEAR_HPP
#define HASHLINEAR_HPP


struct node
{
  int key;
  struct node* next;
};


class HashTable{

private:
  static const int tableSize = 40009;

  int table[tableSize];

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
