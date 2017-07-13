#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
//#include "avlbst.h"

using namespace std;

//Vars
map<int, char> var; //holds t/f/unkonwn value for each var
int size_; //number of variables
int trials_; //number of clauses
vector<vector<int>* > instr; //instructions

//Function headers
bool readIn(char* filename);
bool solve(int curr);
bool runTest(vector<int> clause);
void outputAns(char* filename, bool success);

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    cout << "Usage: ./sat_solver test.cnf test.out" << endl;
  }
  if (!readIn(argv[1]))
    cout << "Error: Problem reading in file" << endl;
  outputAns(argv[2], solve(1));
  return 0;
}

/**
 * Read in from formatted file and set up variables
 *
 * @param filename The filename to read from
 * @return Whether reading in was successful
 */
bool readIn(char* filename)
{
  ifstream fin(filename);
  if(!fin.good()) {//check input file
     cout << "Error: Input file not found\n";
       return false;
   }
   stringstream ss;
   string tmp;
   getline(fin, tmp);
   while (tmp.substr(0, 1).compare("c") == 0)
   {
     getline(fin, tmp);
   }
   if(tmp.substr(0, 1).compare("p") != 0)
     return false;
   ss.str(tmp);
   string tmpss;
   ss >> tmpss;
   ss >> tmpss;
   ss >> size_;
   ss >> trials_;
   ss.str("");
   ss.clear();
   int tmpval =0;
   for(int i = 0; i < trials_; i++)
   {
     getline(fin, tmp);
     ss.str(tmp);
     instr.push_back(new vector<int>);
     while(ss >> tmpval)
     {
       if(tmpval != 0)
         instr[i]->push_back(tmpval);
     }
     ss.str("");
     ss.clear();
   }
   for(int i = 1; i <= size_; i++)
   {
     var.insert(make_pair(i, -1));
   }
   fin.close();
   return true;
}

/**
 * Tests if a given clause will work with the current vars
 *
 * @param clause the clause to run
 * @return True if true (or indeterminate), False if false
 */
bool runTest(vector<int>* clause)
{
  if(clause->size() == 1)
  {
    int tmp = clause->at(0);
    if(tmp< 0)
    {
      tmp = tmp*-1;
      if(var[tmp] == -1) 
        return true;
      return (!var[tmp]);
    }
    else
    {
      if(var[tmp] == -1)
        return true;
      return (var[tmp]);
    }
  }
  for(unsigned int i = 0 ; i < clause->size(); i++)
  {
    for(unsigned int j = i+1; j < clause->size(); j++)
    {
      bool var1f = false;
      bool var2f = false;
      int var1 = clause->at(i);
      if(var1 < 0)
      {
        var1 = -1*var1;
        var1f = true;
      }
      int var2 = clause->at(j);
      if(var2 < 0)
      {
        var2 = -1*var2;
        var2f = true;
      }

      char var1c = var[var1];
      char var2c = var[var2];
      if(var1f)
      {
        if(var1c == 0)
          var1c = 1;
        else if(var1c == 1)
          var1c = 0;
      }
      if(var2f)
      {
        if(var2c == 0)
          var2c = 1;
        else if(var2c == 1)
          var2c = 0;
      }

      if(var1c == -1 || var2c == -1) {}
      else if(var1c || var2c)
      {
        cout << "true" <<endl;
        return true;
      }
    }
  }
  return false;
}


/**
 * Recursive algorithm to solve for the variabls
 *
 * @param i Current variable
 * @return true if solution found, false if no solution
 * exists
 */
bool solve(int curr)
{
  bool solved = false;
  while(!solved)
  {
    bool csolved = true;
    if(curr == size_+1)
      return true; //breakout
    if(var[curr] == 1)
    {
      var[curr] = -1;
      return false; //backtrack
    }
    var[curr] = var[curr]+1;
    cout << (int)var[curr] << endl;
    for(int i = 0; i < trials_; i++)
    {
      if(!runTest(instr[i]))
      {
        csolved = false;
        break;
      }
    }
    if(csolved)
      solved = solve(curr+1);
  }
  return true;
}

/**
 * outputs answer to specified file
 *
 * @param filename filename to output to 
 * @param success whether a solution was found
 */
void outputAns(char* filename, bool success)
{
  ofstream fout(filename);
  if(!success)
  {
    fout << "No solution";
    return;
  }
  for(int i = 1; i <= size_; i++)
  {
    fout << i << " = " << (int)var[i] << "\n";
  }
}
