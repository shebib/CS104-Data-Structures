#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

 private:
    /// Add whatever helper functions and data members you need below

    /**
     * Recursively promote node at location loc until it is 
     * in a valid location 
     */
    void bubUp(size_t loc);
    void bubDown(size_t loc);
    void swap(size_t a, size_t b);
    void print(); //for debugging


 private:
   /// Data members - These should be sufficient
    std::vector< T > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{ 
}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{

}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push( const T& item)
{
  store_.push_back(item);
  keyToLocation_.insert(std::make_pair(item, store_.size() - 1));
  bubUp(store_.size()-1);
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
  PComparator p;
  if(!p(newVal, old))
    return;
  typename std::unordered_map<T, size_t, Hasher, KComparator>::iterator it =  keyToLocation_.find(old);
  if(it == keyToLocation_.end())
    return;
  int loc = it->second;
  store_[loc] = newVal;
  bubUp(loc);
}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    store_[0] = store_.back();
    keyToLocation_.erase(store_.back());
    store_.pop_back();
    bubDown(0);
}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::bubUp(size_t loc)
{
  size_t parent = (loc-1)/m_;
  if(loc == 0)
    return;
  PComparator p;
  if(p(store_[loc],store_[parent]))
  {
    swap(loc, parent);
    bubUp(parent);
  }
  else
    return;
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::bubDown(size_t loc)
{
  T min = store_[loc];
  PComparator p;
  for(int i = 0; i < m_; i++)
  {
    size_t child = loc*m_ + 1 + i;
    if(child > store_.size()-1)
      break;
    min = std::min(min, store_[child], p);
  }
  size_t swapLoc = keyToLocation_[min];
  if(swapLoc == loc)
    return;
  swap(loc, swapLoc);
  bubDown(swapLoc);
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::swap(size_t a, size_t b)
{
  T tmp = store_[a];
  store_[a] = store_[b];
  store_[b] = tmp;
  keyToLocation_[store_[a]] = a;
  keyToLocation_[store_[b]] = b;
}


template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::print()
{
  for(int i = 0; i < store_.size(); i++)
    std::cout << i << ":" << store_[i].num << store_[i].tag << std::endl;
}

#endif

