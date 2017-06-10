#ifndef LLISTSTR_H
#define LLISTSTR_H
#include <string>

class LListStr {
 public:
  struct Item {
    std::string val;
    Item *prev;
    Item *next;
  };

  /**
   * Default constructor 
   */
  LListStr();

  /**
   * Destructor
   */
  ~LListStr();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos
   */
  void insert(int pos, const std::string& val);

  /**
   * Removes the value at index, pos
   */
  void remove(int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set(int pos, const std::string& val);

  /**
   * Returns the value at index, pos
   */
  std::string& get(int pos);

  /**
   * Returns the value at index, pos
   */
  std::string const & get(int pos) const;

  /**
   * Adds an item to the back of the list in O(1) time
   */
  void push_back(const std::string& val);

  /**
   * Copy constructor
   */
  LListStr(const LListStr& other);

  /**
   * Assignment Operator
   */
  LListStr& operator=(const LListStr& other);

  /**
   * Deletes all items in the list
   */
  void clear();

 private:
  /** 
   * Returns a pointer to the item at index, pos
   *  and NULL otherwise
   */
  Item* getNodeAt(int pos) const;

  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif
