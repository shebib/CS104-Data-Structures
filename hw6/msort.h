#include <vector>
#include <iostream>

template <class T, class Comparator>
class MSort {
public:
static void mergeSort(std::vector<T>& arr, Comparator comp)
{
  mHelp(arr, comp, 0, arr.size() - 1);
}

private:
/*
 * left and right are array indices (in the std::vector)
 */
static void mHelp(std::vector<T>& arr, Comparator comp, int left, int right)
{
  if(right - left <= 0) 
    return; //Breakout
  int ll = left;
  int diff = (right - left)/2; 
  int lr = ll + diff;
  int rl = lr + 1;
  int rr = right;
  mHelp(arr, comp, ll, lr);
  mHelp(arr, comp, rl, rr);
  merge(arr, comp, ll, lr, rl, rr);
}

/*
 * merge ll-lr and rl-rr by copying only ll-lr and then merging into arr
 */
static void merge(std::vector<T>& arr, Comparator comp, 
    int ll, int lr, int rl, int rr)
{
  std::vector<T> cp; //copy only left segment (which should be >= right segment)
  for(int i = ll; i <= lr; i++)
  {
    cp.push_back(arr[i]);
  }
  unsigned int lp = 0;
  int rp = rl;
  int curr = ll;
  while(lp < cp.size() && rp <= rr) //merge
  {
    if(comp(cp[lp], arr[rp]))
    {
      arr[curr] = cp[lp];
      curr++;
      lp++;
    }
    else
    {
      arr[curr] = arr[rp];
      curr++;
      rp++;
    }
  }
  while(lp < cp.size()) //dump leftover left arr to arr
  {
    arr[curr] = cp[lp];
    curr++; lp++;
  } // right array is already stored in arr (wasn't copied)
}
};
