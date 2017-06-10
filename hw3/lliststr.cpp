#include "lliststr.h"
#include <cstdlib>
#include <stdexcept>
#include <string>

LListStr::LListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListStr::~LListStr()
{
  clear();
}

bool LListStr::empty() const
{
  return size_ == 0;
}

int LListStr::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListStr::insert(int loc, const std::string& val)
{
    if(loc<0 || loc > size_) //bounds
        return;
    else if(loc == 0) //beginning
    {
        Item* ptra = getNodeAt(loc);
        head_ = new Item;
        head_->next = ptra;
        head_->prev = NULL;
        head_->val = val;
        size_++;
        if(size_  == 1)
            tail_ = head_;
        else 
            ptra->prev = head_;
    }
    else if(loc == size_) //end
    {
        Item* ptrp = getNodeAt(loc-1);
        ptrp->next = new Item;
        Item* curr = ptrp->next;
        curr->prev = ptrp;
        curr->next = NULL;
        curr->val = val;
        size_++;
        tail_ = curr;
    }
    else //middle
    {
        Item* ptra = getNodeAt(loc);
        Item* ptrp = ptra->prev;
        ptrp->next = new Item;
        Item* curr = ptrp->next;
        ptra->prev = curr;
        curr->next = ptra;
        curr->prev = ptrp;
        curr->val = val;
        size_++;
    }
}

/**
 * Complete the following function
 */
void LListStr::remove(int loc)
{
    if(loc <0 || loc > size_-1) //bounds check
        return;
    else if(loc == 0) //beginning of list
    {
        Item* del = getNodeAt(loc);
        Item* ptra = del->next;
        delete del;
        head_ = ptra;
        size_--;
        if(size_ == 0) //list is empty
            tail_ = NULL;
        else
            ptra->prev = NULL;
    }
    else if(loc == size_-1) //end of list
    {
        Item* del = getNodeAt(loc);
        Item* ptrp = del->prev;
        delete del;
        ptrp->next = NULL;
        tail_ = ptrp;
        size_--;
    }
    else //middle of list
    {
        Item* del = getNodeAt(loc);
        Item* ptrp = del->prev;
        Item* ptra = del->next;
        ptrp->next = ptra;
        ptra->prev = ptrp;
        delete del;
        size_--;
    }
}

void LListStr::set(int loc, const std::string& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

std::string& LListStr::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

std::string const & LListStr::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListStr::Item* LListStr::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}

void LListStr::push_back(const std::string& val)
{
    insert(size_, val);
}

LListStr::LListStr(const LListStr& other)
{
    size_ = 0;
    for(int i = 0; i < other.size(); i++)
    {
        insert(i, other.get(i));
    }
}

LListStr& LListStr::operator=(const LListStr& other)
{
    if(this == &other) return *this;
    if(head_) clear();
    size_ = 0;
    for(int i = 0; i < other.size(); i++)
    {
        insert(i, other.get(i));
    }
    return *this;
}
