#include "stackint.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

int main(int argc, char * argv[]) 
{
    if(argc < 3)
        std::cerr << "Usage ./laundry laundry.in laundry.out" << std::endl;
  
    std::ifstream fin(argv[1]);
    StackInt stack;
    if(!fin.good()) {//check input file
        std::cout << "Error: Input file not found";
        exit(1);
    }
    std::ofstream fout(argv[2]);

    int tmp;
    while(fin >> tmp)
    {
        fout << tmp << std::endl;
        if(tmp == -1 || tmp == 0)
            stack.push(tmp);
        else
        {
            for(int i = 0; i < tmp; i++)
            {
                if(stack.empty())
                    break;
                int out = stack.top();
                if(out == -1)
                    fout << "white ";
                else
                    fout << "black ";
                stack.pop();
            }
            fout << std::endl;
        }
    }
    fin.close();
    fout.close();
}

