#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <cstdlib>
#include <iostream>

using namespace std;
template <typename T>

class ListNode{
public:
  ListNode(T data);
  virtual ~ListNode();
  template <typename S>
  friend class DblList;
  template <typename S>
  friend class PQueue;
private:
  T m_data;
  ListNode<T>* m_next;
  ListNode<T>* m_prev;
};

#endif