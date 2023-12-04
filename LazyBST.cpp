#include "LazyBST.h"
#include "TreeNode.cpp"
#include <cmath>

static int const log32(int n)
{
  double const log23 = 1.7;
  return (int)ceil(log23 * log(n));
}

template <typename T>
LBST<T>::LBST(){
  m_root = NULL;
  m_size = 0;
}

template <typename T>
LBST<T>::~LBST(){
  if(m_root != NULL){
    delete m_root;
  }
}

template <typename T>
int LBST<T>::getSize(){
  return m_size;
}

template <typename T>
bool LBST<T>::insert(T d){
  TreeNode<T>* node = new TreeNode<T>(d);
  int height = insertWithDepth(node);
  ++m_m;
  if (height > log32(m_size)){
    TreeNode<T>* parent = node->m_parent;
    while (3 * getNodeSize(parent) <= 2 * getNodeSize(parent->m_parent)){
      parent = parent->m_parent;
    }
    buildTree(parent->m_parent);
  }
  return height >= 0;
}

template <typename T>
int LBST<T>::insertWithDepth(TreeNode<T>* insertNode){
  TreeNode<T>* curr = m_root;
  if (curr == NULL){
    m_root = insertNode;
    m_size++;
    return 0;
  }
  bool isInserted = false;
  int depth = 0;
  do{
    if(*insertNode->m_data < *curr->m_data){
      if(curr->m_left == NULL){
        curr->m_left = insertNode;
        insertNode->m_parent = curr;
        isInserted = true;
      }else{
        curr = curr->m_left;
      }
    }else if(*insertNode->m_data > *curr->m_data){
      if(curr->m_right == NULL){
        curr->m_right = insertNode;
        insertNode->m_parent = curr;
        isInserted = true;
      }else{
        curr = curr->m_right;
      }
    }else{
      return -1;
    }
    depth++;
  }
  while (!isInserted);
  m_size++;
  return depth;
}

template <typename T>
bool LBST<T>::contains(T d){
    return helper(m_root,d);
}

template <typename T>
bool LBST<T>::helper(TreeNode<T>* subTreeRoot, T d){
  if(subTreeRoot == NULL){
    return false;
  } else if (subTreeRoot->m_data == d){
    return true;
  } else if(d < subTreeRoot->m_data){
    return helper(subTreeRoot->m_left,d);
  } else{
    return helper(subTreeRoot->m_right,d);
  }
}

template <typename T>
void LBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && target->m_data != key){
    parent = target;
    if(key < target->m_data){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}

template <typename T>
void LBST<T>::remove(T d){
  TreeNode<T>* parent = NULL;
  TreeNode<T>* target = NULL;
  //do the remove
  target = m_root;
  findTarget(d,target,parent);
   if(target == NULL){ //not in tree
    return;
  }
  //do some real work
  if(target->m_left == NULL && target->m_right == NULL ){
    if(target == m_root){
      m_root = NULL;
      --m_size;
      if(m_m > 2 * m_size){
        buildTree(m_root);
        m_m = m_size;
      }
    } else{
      if(target == parent->m_left){
        parent->m_left = NULL;
        --m_size;
        if(m_m > 2 * m_size){
        buildTree(m_root);
        m_m = m_size;
      }
      } else{
        parent->m_right = NULL;
        --m_size;
        if(m_m > 2 * m_size){
        buildTree(m_root);
        m_m = m_size;
        }
      }
    }
  } else if(target->m_left != NULL && target->m_right != NULL){ //2 children
    T succValue = getSuccessor(target->m_right);
    remove(succValue);
    target->m_data = succValue;
  } else{ // 1 child
    TreeNode<T>* child;
    if(target->m_left != NULL){
      child = target->m_left;
    } else{
      child = target->m_right;
    }
    if(target == m_root){
      m_root = child;
    } else{
      if(target == parent->m_left){
        parent->m_left = child;
      } else{
        parent->m_right = child;
      }
    }
  }
}

template <typename T>
int LBST<T>::storeArray(TreeNode<T>* node, TreeNode<T>* arr[], int i)
{
  if (node == NULL){
    return i;
  }
  
  i = storeArray(node->m_left, arr, i);
  arr[i++] = node;
  return storeArray(node->m_right, arr, i);
}

template <typename T>
int LBST<T>::getNodeSize(TreeNode<T>* node){
    if (node == NULL){
        return 0;
    }else{
        return(getNodeSize(node->m_left) + 1 + getNodeSize(node->m_right));
    }
}

template <typename T>
TreeNode<T>* LBST<T>::buildWithArray(TreeNode<T>** arr, int i, int n){
    if (n == 0){ 
        return NULL;
    }

    int center = n / 2; 

    arr[i + center]->m_left = buildWithArray(arr, i, center); 
 
    if (arr[i + center]->m_left != NULL){
        arr[i + center]->m_left->m_parent = arr[i + center];
    }

    arr[i + center]->m_right = buildWithArray(arr, i + center + 1, n - center - 1);

    if (arr[i + center]->m_right != NULL){
        arr[i + center]->m_right->m_parent = arr[i + center];
    }

    return arr[i + center];
}

template <typename T>
void LBST<T>::buildTree(TreeNode<T>* node){
  int n = getNodeSize(node);
  TreeNode<T>* parent = node->m_parent;
  TreeNode<T>** arr = new TreeNode<T>*[n];
  storeArray(node, arr, 0);
  if (parent == NULL)
  {
    m_root = buildWithArray(arr, 0, m_size);
    m_root->m_parent = NULL;
  }
  else if (parent->m_right == node)
  {
    parent->m_right = buildWithArray(arr, 0, m_size);
    parent->m_right->m_parent = parent;
  }
  else
  {
    parent->m_left = buildWithArray(arr, 0, m_size);
    parent->m_left->m_parent = parent;
  }
}

template <typename T>
T LBST<T>::getSuccessor(TreeNode<T>* node){ 
  while(node->m_left != NULL){
    node = node->m_left;
  }
  return node->m_data;
}

template <typename T>
T LBST<T>::getMedian(){
  return m_root->m_data;
}

template <typename T>
T LBST<T>::getMin(){
  return getMinHelper(m_root);
}

template <typename T>
T LBST<T>::getMax(){
  return getMaxHelper(m_root);
}

template <typename T>
T LBST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_left == NULL){
    return subTreeRoot->m_data;
  } else{
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T>
T LBST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_right == NULL){
    return subTreeRoot->m_data;
  } else{
    return getMaxHelper(subTreeRoot->m_right);
  }
}

template <typename T>
void LBST<T>::printByOrder(){
  printByOrderHelper(m_root);
}

template <typename T>
void LBST<T>::printByOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printByOrderHelper(subTreeRoot->m_left);
    cout << subTreeRoot->m_data->getId() << endl;
    printByOrderHelper(subTreeRoot->m_right);
  }
}

template <typename T>
void LBST<T>::printPostOrder(){
  printPostOrderHelper(m_root);
}

template <typename T>
void LBST<T>::printPostOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printPostOrderHelper(subTreeRoot->m_left);
    printPostOrderHelper(subTreeRoot->m_right);
    cout << subTreeRoot->m_data << endl;
  }
}

template <typename T>
TreeNode<T>* LBST<T>::getRoot(){
  return m_root;
}

template <typename T>
T LBST<T>::getWithId(int id){
  getWithIdHelper(m_root, id);
  return found;
}


template <typename T>
void LBST<T>::getWithIdHelper(TreeNode<T>* subTreeRoot, int id){
  if(subTreeRoot == NULL){
        found = NULL;
    }else if(id == subTreeRoot->getData()->getId()){
        found = subTreeRoot->getData();
    }else if(id < subTreeRoot->getData()->getId()){
        getWithIdHelper(subTreeRoot->getLeft(), id);
    }else{
        getWithIdHelper(subTreeRoot->getRight(), id);
    }
}

template <typename T>
void LBST<T>::getWithIdThenPrint(int id){
  getWithIdThenPrintHelper(m_root, id);
}

template <typename T>
TreeNode<T>* LBST<T>::getWithIdThenPrintHelper(TreeNode<T>* subTreeRoot, int id){
  if(subTreeRoot == NULL){
        return NULL;
    }else if(id == subTreeRoot->getData()->getId()){
        cout << *subTreeRoot->getData() << endl;
        return subTreeRoot;
    }else if(id < subTreeRoot->getData()->getId()){
        getWithIdThenPrintHelper(subTreeRoot->getLeft(), id);
    }else{
        getWithIdThenPrintHelper(subTreeRoot->getRight(), id);
    }
}

template <typename T>
bool LBST<T>::existingId(int id){
  if(id == -1){
    return false;
  }else if(id == m_root->getData()->getId()){
      return true;
  }else{
      existingIdHelper(m_root, id);
      return m_unique == 1;
  }
}

template <typename T>
void LBST<T>::existingIdHelper(TreeNode<T>* subTreeRoot, int id){
    if(subTreeRoot == NULL){
        m_unique = false;
    }else if(subTreeRoot->getData()->getId() == id){
        m_unique = true;
    }else if(subTreeRoot->getData()->getId() > id){
        existingIdHelper(subTreeRoot->getLeft(), id);
    }else{
        existingIdHelper(subTreeRoot->getRight(), id);
    }
}

template <typename T>
void LBST<T>::printInfo(){
    printInfoHelper(m_root);
}

template <typename T>
void LBST<T>::printInfoHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
      printInfoHelper(subTreeRoot->getLeft());
      cout << *subTreeRoot->getData() << endl;
      printInfoHelper(subTreeRoot->getRight());
  }
}

template <typename T>
void LBST<T>::outputInfo(){
  outputInfoHelper(m_root);
}

template <typename T>
void LBST<T>::outputInfoHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    outputInfoHelper(subTreeRoot->getLeft());
    std::ofstream file;
    file.open("runLog.txt", std::ios_base::app);
    file << *subTreeRoot->getData() << endl;
    file.close();
    outputInfoHelper(subTreeRoot->getRight());
  }
}