#ifndef DLL_H
#define DLL_H

struct Node {
  int key;
  Node* next;
  Node* prev;
};


class DLL {
  public:
    DLL(); // constructor
    void insert(int key);
    int insert2(int key);
    Node* search(int key);
    int search2(int key);
    void display();
  private:
  Node* head = nullptr;
};

#endif
