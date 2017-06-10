#ifndef SETSTR_H
#define SETSTR_H
#include <string>
#include "lliststr.h"

class SetStr {
 public:
  /**
   * Default constructor 
   */
  SetStr();

  /**
   * Destructor
   */
  ~SetStr();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val into the set, do nothing if val already exists
   */
  void insert(const std::string& val);

  /**
   * Removes the value from the set, do nothing if it doesn't exist
   */
  void remove(const std::string& val);

  /**
   * Returns true if the item is in the set
   */
  bool exists(const std::string& val) const;

  /**
   * Return a pointer to the first item
   *  and support future calls to next()
   */
  std::string const* first();

  /**
   * Return a pointer to the next item
   *  after the previous call to next
   *  and NULL if you reach the end
   */
  std::string const* next();

  /**
   * Returns another (new) set that contains
   * the union of this set and "other"
   */
  SetStr setUnion(const SetStr& other) const;

  /**
   * Returns another (new) set that contains
   * the intersection of this set and "other"
   */
  SetStr setIntersection(const SetStr& other) const;

  SetStr operator|(const SetStr& other) const;

  SetStr operator&(const SetStr& other) const;


 private:
  LListStr list_;
  int curr_; //point to current position in list

  /**
   * Declare other members here as needed
   */

};

#endif
