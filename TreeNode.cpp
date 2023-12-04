#include "TreeNode.h"

template <typename T>
TreeNode<T>::TreeNode(T d){
    m_data = d;
    m_left = NULL;
    m_right = NULL;
}


template <typename T>
TreeNode<T>::~TreeNode(){
    if(m_left != NULL){
        delete m_left;
    }
    if(m_right != NULL){
        delete m_right;
    }
}

template <typename T>
T TreeNode<T>::getData(){
    return m_data;
}

template <typename T>
TreeNode<T>* TreeNode<T>::getLeft(){
    return m_left;
}

template <typename T>
TreeNode<T>* TreeNode<T>::getRight(){
    return m_right;
}