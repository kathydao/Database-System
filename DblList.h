#ifndef DBL_LIST_H
#define DBL_LIST_H

#include "ListNode.cpp"
#include <iostream>

using namespace std;
template <typename T>

class DblList{
public:
  DblList();
  virtual ~DblList();
  void print();
  int getSize();
  bool isEmpty();
  void addBack(T data);
  void addFront(T data);
  void add(int pos, T data); 
  T removeBack();
  T removeFront();
  T remove(int pos);
  T removeSpecific(T data);
  T get(int pos);
  bool contains(T data);
protected:
  ListNode<T>* m_front;
  ListNode<T>* m_back;
  int m_size;
};
#endif