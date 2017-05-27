#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

/*
 * sums pairs from outside to in
 * Args: input.txt output.txt
 * Daniel Shebib
*/
int main(int argc, char * argv[])
{
    if(argc != 3) { //Check number of arguments 
        cout << "Error: Please enter 2 arguments: [[input.txt]] [[output.txt]]";
        exit(1);
    }
    
    ifstream fin(argv[1]);
    if (!fin.good()) { //check if file exists
        cout << "Error: File not found";
        fin.close();
        exit(1);
    }

    ofstream fout; //initialize file output
    fout.open(argv[2]);
    if(!fout.is_open()) {//make sure output file opens
        cout << "Error: Could not create output file";
        fin.close();
        fout.close();
        exit(1);
    }

    int size = 0;
    fin >> size;
    if (size  == 0) { //check first int for 0 and invalid ranges
        fout << "0";
        fin.close();
        fout.close();
        exit(1);
    }
    if (size  < 0) {
        cout << "Please start with the number of lines in the file (not negative)";
        fin.close();
        fout.close();
        exit(1);
    }
    int * arr = new int[size]; //dynamically create array and store integers from file
    for(int i = 0; i < size; i++)
    {
        fin >> arr[i];
    }

    int * out = new int[size/2+1];
    for(int i = 0; i < size/2+1; i++)
    {
        out[i] = arr[i] + arr[size-i-1]; //perform sum and store in out
    }

    for(int i = 0; i < size/2+1; i++) //output to file
    {
        fout << out[i] << "\n";
    }

    //clean up
    fin.close();
    fout.close();
    delete[] arr;
    delete[] out;
}
