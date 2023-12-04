#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
template <typename T>

class TreeNode{
public:
    TreeNode(T d);
    virtual ~TreeNode();
    T getData();
    TreeNode<T>* getRight();
    TreeNode<T>* getLeft();
    template <typename S>
    friend class LBST;
private:
    T m_data;
    TreeNode<T>* m_parent;
    TreeNode<T>* m_left;
    TreeNode<T>* m_right;
};

#endif