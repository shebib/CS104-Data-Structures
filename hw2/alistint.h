#ifndef ALISTINT_H
#define ALISTINT_H

class AListInt
{
 public:
  /**
   * Default constructor - default to a list of capacity = 10
   */
  AListInt();

  /**
   * Another constructor - default to a list to the indicated capacity
   */
  AListInt(int cap);
  
  /**
   * Destructor
   */
  ~AListInt();
  
  /**
   * Standard List interface
   */

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
  void insert (int pos, const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove (int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set (int position, const int& val);

  /**
   * Returns the value at index, pos
   */
  int& get (int position) ;

  /**
   * Returns the value at index, pos
   */
  int const & get (int position) const;
  
 private:
  /**
   * Should double the size of the list maintaining its contents
   */
  void resize(); 
   
  /* Add necessary data members here */
  
  int * arr_;
  int size_;
  int maxsize_;
  
};

#endif
