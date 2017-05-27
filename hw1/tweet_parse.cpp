#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;

void readTweets(char* filelname, vector<string>& tweets); //Read in tweets from file to vector
bool push_back_unique(vector<string>& vec, string str); //push_back vector only if str is unique

/* Reads in tweets from file and gets unique users and hashtags, sending them to cout
 * Args: input.txt
 * Daniel Shebib
*/
int main(int argc, char * argv[]) 
{
    vector<string> tweets;
    vector<string> users;
    vector<string> hashtags;

    readTweets(argv[1], tweets); //read tweets to vector

    for(int i = 0; (unsigned)i<tweets.size(); i++) //parse users
    {
        string tmp = tweets[i];
        int pos = 0;
        pos = tmp.find("@");
        while(pos != -1)
        {
            stringstream ss(tmp.substr(pos));
            string usr;
            ss >> usr;
            push_back_unique(users, usr);
            pos = tmp.find("@", pos+1);
        }
    }

    for(int i = 0; (unsigned)i<tweets.size(); i++) //parse hashtags
    {
        string tmp = tweets[i];
        int pos = 0;
        pos = tmp.find("#");
        while(pos != -1)
        {
            stringstream ss(tmp.substr(pos));
            string hash;
            ss >> hash;
            push_back_unique(hashtags, hash);
            pos = tmp.find("#", pos+1);
        }
    }

    //output
    cout << "1. Number of tweets=" << tweets.size() << endl;
    cout << "2. Unique users" << endl;
    for(int i = 0; (unsigned)i<users.size(); i++)
    {
        cout << users[i] << endl;
    }
    cout << "3. Unique hashtags" << endl;
    for(int i = 0; (unsigned)i<hashtags.size(); i++)
    {
        cout << hashtags[i] << endl;
    }

    return 0;
}

void readTweets(char* filename, vector<string>& tweets)
{
    ifstream fin(filename);
    if(!fin.good()) {//check input file
        cout << "Error: Input file not found";
        exit(1);
    }
    while(fin.peek() != EOF)
    {
        string tmp;
        getline(fin, tmp);
        if(!tmp.empty()) {//ignore empty tweets
            tweets.push_back(tmp);
        }
    }
    fin.close();
}

bool push_back_unique(vector<string>& vec, string str)
{
    for(int i = 0; (unsigned)i<vec.size(); i++)
    {
        if(vec[i].compare(str) == 0) {//check string
            return false;
        }
    }
    vec.push_back(str);
    return true;
}
