#include "ListNode.h"

template <typename T>
ListNode<T>::ListNode(T data){
  m_data = data;
  m_next = NULL;
  m_prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  m_next = NULL;
  m_prev = NULL;
}