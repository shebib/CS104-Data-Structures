#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Reads in words and recursively generates sentences combining them
 * Args: input.txt output.txt
 * Order: adj, subject, verb, adverb in new lines. 1 adj and/or adv per sentence
 * Daniel Shebib 
*/
void readWords(char* filename, vector<vector<string> >& words);
// client interface

void generateSentences(vector<vector<string> >& words, ofstream& ofile);
// recursive helper function

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words)
{
    ifstream fin(filename);
    if(!fin.good()) {//check input file
        cout << "Error: Input file not found";
        exit(1);
    }
    for(int i = 0; (i < 4 && fin.peek() != EOF); i++)
    {
        string tmp;
        getline(fin, tmp);
        stringstream ss(tmp);
        vector<string> subvec;
        while(ss.peek() != EOF)
        {
            string tmp2;
            ss >> tmp2;
            subvec.push_back(tmp2);
        }
        words.push_back(subvec);
    }  
}

void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
    words[0].insert(words[0].begin(), ""); //insert gaps for possibility of no adj/adverb
    words[3].insert(words[3].begin(), "");
    int numSentences = 0;
    genHelper(words, ofile, 0, "",  numSentences); //call helper function for recursion
    ofile << numSentences << " sentences." << endl;
    words[0].erase(words[0].begin()); //restore state of vector
    words[3].erase(words[3].begin());

}

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences)
{
    if(currentOption >= 4) {//breakout
        ofile << "The " << sentence.substr(0, sentence.length()-1) << "." << endl;
        numSentences++;
    }
    else
    {
        for(int i = 0; (unsigned)i<words[currentOption].size(); i++) //iterate through current word options
        {
            sentence = sentence + words[currentOption][i];
            int len = words[currentOption][i].length(); //keep track of length added to sentence
            if (!words[currentOption][i].empty()) { //add space if word was added to sentence
                sentence += " ";
                len++;
            }
            genHelper(words, ofile, currentOption+1, sentence, numSentences);
            sentence = sentence.substr(0, sentence.length()-len);
        }
    }
  
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
