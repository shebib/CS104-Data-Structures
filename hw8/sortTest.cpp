/*#include "msort.h"
#include <iostream>
#include <cstdlib>
using namespace std;

struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };

  struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };


int main()
{
    string s1 = "Blue";
  string s2 = "Red";
  AlphaStrComp comp1;
  LengthStrComp comp2;

  cout << "Blue compared to Red using AlphaStrComp yields " << comp1(s1, s2) << endl;
  // notice comp1(s1,s2) is calling comp1.operator() (s1, s2);
  cout << "Blue compared to Red using LenStrComp yields " << comp2(s1, s2) << endl;
  // notice comp2(s1,s2) is calling comp2.operator() (s1, s2);
  
  vector<string> array; 
  array.push_back("b");
  array.push_back("aa");
  array.push_back("cc");
  array.push_back("ggggg");
  array.push_back("eee");
  array.push_back("d");
  array.push_back("h");
  array.push_back("ff");
  
  for(int i = 0; i < array.size(); i++)
  {
    cout << array[i];
  }
  cout << endl;

  MSort<std::string, AlphaStrComp>::mergeSort(array, comp1);

  for(int i = 0; i < array.size(); i++)
  {
    cout << array[i];
  }
  cout << endl; 
}
*/
