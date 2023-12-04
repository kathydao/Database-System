#ifndef LazyBST_H
#define LazyBST_H

#include "TreeNode.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
template <typename T>

class LBST{
public:
  LBST();
  virtual ~LBST();
  bool insert(T d);
  void remove(T d);
  bool contains(T d);
  void printByOrder();
  void printPostOrder();
  T getMin();
  T getMax();
  T getMedian();
  int getSize();
  TreeNode<T>* getRoot();
  T getWithId(int id);
  void getWithIdThenPrint(int id);
  bool existingId(int id);
  void printInfo();
  void outputInfo();
private:
  TreeNode<T>* m_root;
  int m_size;
  int m_m; 
  bool m_unique;
  T found;
  bool helper(TreeNode<T>* subTreeRoot, T d);
  void printByOrderHelper(TreeNode<T>* subTreeRoot);
  void printPostOrderHelper(TreeNode<T>* subTreeRoot);
  T getMinHelper(TreeNode<T>* subTreeRoot);
  T getMaxHelper(TreeNode<T>* subTreeRoot);
  void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
  T getSuccessor(TreeNode<T>* node);
  int storeArray(TreeNode<T>* ptr, TreeNode<T>* arr[], int i);
  TreeNode<T>* buildWithArray(TreeNode<T>** arr, int i, int n);
  int insertWithDepth(TreeNode<T>* node);
  int getNodeSize(TreeNode<T>* node);
  void buildTree(TreeNode<T>* node);
  void getWithIdHelper(TreeNode<T>* subTreeRoot, int id);
  TreeNode<T>* getWithIdThenPrintHelper(TreeNode<T>* subTreeRoot, int id);
  void existingIdHelper(TreeNode<T>* subTreeRoot, int id);
  void printInfoHelper(TreeNode<T>* subTreeRoot);
  void outputInfoHelper(TreeNode<T>* subTreeRoot);
};

#endif