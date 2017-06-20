#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include "datetime.h"
#include "tweet.h"
#include "twiteng.h"
using namespace std;

void displayTweets(vector<Tweet*>& hits)
{
  for(vector<Tweet*>::iterator it = hits.begin(); it != hits.end(); it++)
  {
    cout << **it << endl;
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide the twitter data file" << endl;
    return 1;
  }
  TwitEng twit;

  if ( twit.parse(argv[1]) ){
    cerr << "Unable to parse " << argv[1] << endl;
    return 1;
  }

  while(true)
  {
    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  TWEET username tweet_text" << endl;
    cout << "  QUIT (and write feed files)        " << endl;
    cout << "=====================================" << endl;
    string in;
    cin >> in;
    if(in.substr(0, 3).compare("AND") == 0) //search AND
    {
      std::getline(cin, in);
      in = in.substr(1);
      vector<string> terms;
      stringstream ss;
      ss.str(in);
      string tmp;
      while(ss >> tmp)
      {
        terms.push_back(tmp);
      }
      vector<Tweet*> found = twit.search(terms, 0);
      for(vector<Tweet*>::iterator it = found.begin(); it != found.end(); it++)
      {
        cout << **it << endl;
      }
    }
    else if(in.substr(0, 2).compare("OR") == 0) //search OR
    {
      std::getline(cin, in);
      in = in.substr(1);
      vector<string> terms;
      stringstream ss;
      ss.str(in);
      string tmp;
      while(ss >> tmp)
      {
        terms.push_back(tmp);
      }
      vector<Tweet*> found = twit.search(terms, 1);
      for(vector<Tweet*>::iterator it = found.begin(); it != found.end(); it++)
      {
        cout << **it << endl;
      }
    }
    else if(in.substr(0, 5).compare("TWEET") == 0)
    {
      std::getline(cin, in);
      in = in.substr(1);
      time_t rawtime;
      struct tm * tim;
      time (&rawtime);
      tim = localtime(&rawtime);
      DateTime dt(tim->tm_hour, tim->tm_min, tim->tm_sec, tim->tm_year+1900, tim->tm_mon+1, tim->tm_mday);
      string name = in.substr(0, in.find(" "));
      string text = in.substr(in.find(" ")+1);
      try
      {
        twit.addTweet(name, dt, text);
      }
      catch (string& name)
      {
        cout << "Error: Could not find user: " << name << endl;
      }
    }
    else if(in.substr(0, 4).compare("QUIT") == 0)
    {
      twit.dumpFeeds();
      exit(0);
    }
    else
    {
      cout << "Error: invalid command" << endl;
    }
  }
      


  return 0;
}
