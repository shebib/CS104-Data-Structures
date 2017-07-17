#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"

template<typename Key, typename Value>
class SplayTree : public BinarySearchTree<KeyType, ValueType>
{
 public:
  SplayTree();
  ~SplayTree();
  
  // All of the basic operations that one would perform on a map. 
  // Do not change these function definitions, but you may add others
  void insert(const std::pair<Key, Value>& keyValuePair);
  void clear();
  iterator find(const Key& k); // remember a find
                               // also requires splaying
  Value& operator[](const Key& k);
  
 private:
  // Add any private data members and member functions as needed. 
  void splay(Node* n);

};


template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
  if(this->mRoot == NULL)
  {
    this->mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
  }
  else if(this->internalFind(keyValuePair.first)!= NULL) {}
  else
  {
    Key key = keyValuePair.first;
    Node<Key, Value>* curr = this->mRoot;
    Node<Key, Value>* prev = this->mRoot;
    bool left = true;
    while (curr)
    {
        if (key < curr->getKey())
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
      prev->setLeft(new Node<Key, Value>(key, keyValuePair.second, prev));
      splay(prev->getLeft());
    }
    else
    {
      prev->setRight(new Node<Key, Value>(key, keyValuePair.second, prev));
      splay(prev->getRight());
    }
  }
}

template<typename Key, typename Value>
  void SplayTree<Key, Value>::clear()
{ clearHelper(mRoot); mRoot = NULL;}

template<typename Key, typename Value>
void SplayTree<Key, Value>::clearHelper(Node<Key, Value>* n)
{
  if(n->getLeft() != NULL)
    clearHelper(n->getLeft());
  if(n->getRight() != NULL)
    clearHelper(n->getRight());
  delete n;
}

template<typename Key, typename Value>
  iterator SplayTree<Key, Value>::find(const Key& k)
{
  iterator it = iterator(internalFind(key));
  if(it != this->end())
    splay(it.mCurrent);
  return it;
}
    
template<typename Key, typename Value>
  void SplayTree<Key, Value>::splay(Node<Key, Value>* n)
{
  Node<Key, Value>* p;
  Node<Key, Value>* g;
  if(n == mRoot)
    return;
  else if(n->getParent() == mRoot)
  {
    p = n->getParent();
    if(n == p->getLeft())
      rightRotate(p);
    else
      leftRotate(p);
    splay(n);
  }
  else
  {
    g = p->getParent();
    bool nl = false;
    bool pl = false;
    if(p->getLeft() == n)
      nl = true;
    if(g->getLeft() == p)
      pl = true;
    if(!nl && pl)
    {
      rotateLeft(p);
      rotateRight(g);
    }
    else if(nl && !pl)
    {
      rotateRight(p);
      rotateLeft(g);
    }
    else if(nl && pl)
    {
      rotateRight(p);
      n->setParent(g->getParent);
      if(g->getParent() == NULL)
        mRoot = n;
      else
      {
        if(g->getParent()->getLeft = g)
          g->getParent()->setLeft(n);
        else
          g->getParent()->setRight(n);
      }
      Node*<Key, Value> inner = p->getLeft();
      p->setRight(g);
      g->setParent(p);
      g->setLeft(inner);
      if(inner != NULL)
        inner->setParent(g);
    }
    else
    {
      rotateLeft(p);
      n->setParent(g->getParent);
      if(g->getParent() == NULL)
        mRoot = n;
      else
      {
        if(g->getParent()->getLeft = g)
          g->getParent()->setLeft(n);
        else
          g->getParent()->setRight(n);
      }
      Node*<Key, Value> inner = p->getRight();
      p->setLeft(g);
      g->setParent(p);
      g->setRight(inner);
      if(inner != NULL)
        inner->setParent(g);
    }
    splay(n);
  }
}

template<typename Key, typename Value>
  Value& SplayTree<Key, Value>::operator[](const Key& k)
{
  iterator it = find(k);
  if(it == end())
  {
    insert(std::make_pair(k, Value()));
    return mRoot->second;
  }
  else
  {
    return it->second;
  }
}

/**
* Rotates n down and to the left. Does not update balance
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateLeft (Node<Key, Value> *n)
{ //TODO
  Node<Key, Value>* parent = n->getParent();
  Node<Key, Value>* inner = n->getRight()->getLeft();
  Node<Key, Value>* y = n->getRight();
  if(parent == NULL) 
    this->mRoot = y;
  else if(parent->getLeft() == n)//connect y to parent
    parent->setLeft(y);
  else
    parent->setRight(y);
  y->setParent(parent);
  y->setLeft(n);//move n (x)
  n->setParent(y);
  n->setRight(inner);//move inner
  if(inner != NULL)
    inner->setParent(n);
}

/**
* Rotates n down and to the right. Does not update balance
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateRight (Node<Key, Value> *n)
{ //TODO
  Node<Key, Value>* parent = n->getParent();
  Node<Key, Value>* inner = n->getLeft()->getRight();
  Node<Key, Value>* y = n->getLeft();
  if(parent == NULL)
    this->mRoot = y;
  else if(parent->getLeft() == n)//connect y to parent
    parent->setLeft(y);
  else
    parent->setRight(y);
  y->setParent(parent);
  y->setRight(n);//move n (x)
  n->setParent(y);
  n->setLeft(inner);//move inner
  if(inner != NULL)
    inner->setParent(n);
}
