#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */
    void insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n);
    void eraseFix(AVLNode<Key, Value> *n, char diff);

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{ //TODO
  if(mRoot = NULL)
  {
    mRoot = new AVLNode(keyValuePair.first, keyValuePair.second, NULL);
  }
  else if(internalFind(keyValuePair.first)!= NULL) {}
  else
  {
    Key key = keyValuePair.first;
    AVLNode<Key, Value>* curr = mRoot;
    AVLNode<Key, Value>* prev = mRoot;
    bool left = true;
    while (curr)
    {
        else if (key < curr->getKey())
        {
          prev = curr;
          curr = curr->getLeft();
          left = true;
        }
        else
        {
          prev = curr;
          curr = curr->getRight();
          left = false;
        }
    }
    if(left)
    {
      prev->setLeft(new ALVNode(key, keyValuePair.second, prev));
      if(prev->getBalance() == 0)
      {
        prev->setBalance(-1);
        insertFix(prev, prev->left);
      }
    }
    else
    {
      prev->setRight(new ALVNode(key, keyValuePair.second, prev));
      if(prev->getBalance() == 0)
      {
        prev->setBalance(1);
        insertFix(prev, prev->right);
      }
    }
  }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{ //TODO
  AVLNode<Key, Value>* n = internalFind(key);
  if(n->getLeft() != NULL && n->getRight() != NULL)
  {
    AVLNode<Key, Value>* tmp = n;
    if(tmp->getRight()!=NULL) //inorder for tmp
    {
      tmp = tmp->getRight();
      while(tmp->getLeft() != NULL)
      {
        tmp = tmp->getLeft();
      }
    }
    else
    {
      AVLNode<Key, Value>* prev = tmp;
      tmp = tmp->getParent();
      while(tmp->getRight() == prev)
      {
        tmp = tmp->getParent();
      }
    }
    nodeSwap(tmp, n);
  }
  AVLNode<Key, Value>* p = n.getParent();
  char diff = 0;
  if(p!= NULL)
  {
    if(p.getLeft() == n)
    {
      diff = 1;
      p.setLeft(n.getLeft());
    }
    else
    {
      diff = -1;
      p.setRight(n.getRight());
    }
  }
  delete n;
  removeFix(p, diff);
}

/*
 * Recursive function to balance tree after insertion.
 */
void insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n)
{ //TODO
  if(p == NULL || p->getParent() == NULL)
    return;
  AVLNode<Key, Value>* g = p->getParent();
  if(g->getLeft() == p) //Left child
  {
    g.updateBalance(-1);
    if(g.getBalance() == 0)
      return;
    else if(g.getBalance() == -1)
      insertFix(g, p);
    else //g.balance == -2
    {
      bool zag = false;
      if((g->getLeft() == p && p->getLeft() == n) || 
          (g->getRight() == p && p->getRight() == n))
        zag = false;
      else
        zag = true;
      if(!zag)
      {
        rotateRight(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      else
      {
        rotateLeft(p);
        rotateRight(g);
        if(n.getBalance() == -1)
        {
          p.setBalance(0);
          g.setBalance(1);
          n.setBalance(0);
        }
        else if(n.getBalance() == 0)
        {
          p.setBalance(0);
          g.setBalance(0);
          n.setBalance(0);
        }
        else
        {
          p.setBalance(-1);
          g.setBalance(0);
          n.setBalance(0);
        }
      }
    }
  }
  else //right child
  {
    g.updateBalance(1);
    if(g.getBalance() == 0)
      return;
    else if(g.getBalance() == 1)
      insertFix(g, p);
    else //g.balance == 2
    {
      bool zag = false;
      if((g->getLeft() == p && p->getLeft() == n) || 
          (g->getRight() == p && p->getRight() == n))
        zag = false;
      else
        zag = true;
      if(!zag)
      {
        rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      else
      {
        rotateRight(p);
        rotateLeft(g);
        if(n.getBalance() == 1)
        {
          p.setBalance(0);
          g.setBalance(-1);
          n.setBalance(0);
        }
        else if(n.getBalance() == 0)
        {
          p.setBalance(0);
          g.setBalance(0);
          n.setBalance(0);
        }
        else
        {
          p.setBalance(1);
          g.setBalance(0);
          n.setBalance(0);
        }
      }
    }
  }       
}

/*
 * Recursive function to balance tree after erase.
 */
void eraseFix(AVLNode<Key, Value> *n, char diff)
{ //TODO
  

}


/**
* Rotates n down and to the left. Does not update balance
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{ //TODO
  AVLNode<Key, Value>* parent = n->getParent();
  AVLNode<Key, Value>* left = n->getLeft();
  AVLNode<Key, Value>* inner = n->getRight()->getLeft();
  AVLNode<Key, Value>* y = n->getRight();
  if(parent == NULL) {}
  else if(parent->getLeft() == n)//connect y to parent
    parent->setLeft(y);
  else
    parent->setRight(y);
  y->setParent(parent);
  y->setLeft(n);//move n (x)
  n->setParent(y);
  n->setRight(inner);//move inner
  inner->setParent(n);
}

/**
* Rotates n down and to the right. Does not update balance
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{ //TODO
  AVLNode<Key, Value>* parent = n->getParent();
  AVLNode<Key, Value>* right = n->getRight();
  AVLNode<Key, Value>* inner = n->getLeft()->getRight();
  AVLNode<Key, Value>* y = n->getLeft();
  if(parent == NULL) {}
  else if(parent->getLeft() == n)//connect y to parent
    parent->setLeft(y);
  else
    parent->setRight(y);
  y->setParent(parent);
  y->setRight(n);//move n (x)
  n->setParent(y);
  n->setLeft(inner);//move inner
  inner->setParent(n);
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
