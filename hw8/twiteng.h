#ifndef TWITENG_H
#define TWITENG_H
#include <stack>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "user.h"
#include "datetime.h"
#include "tweet.h"
#include "tagdata.h"
#include "heap.h"


class TwitEng
{

 public:
  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(std::string& username, DateTime& time, std::string& text);

    /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();

  /* You may add other member functions */

  std::vector<std::string> getUserNames();

  std::vector<std::string> getFollowing(std::string usr);

  const std::string getDMFeed(std::string name);

  const std::string getFeed(std::string name);

  void follows(std::string usr, std::string usr2);

  void saveToFile(std::string filename);

  void saveComponentsToFile(std::string filename);

  const std::vector<std::string> searchTweets(std::vector<std::string>& terms, int strategy);

  const std::vector<std::string> getTrending();

  bool login(std::string username, std::string password);

  bool registerUser(std::string username, std::string password);

   private:
  //Variables
  std::vector<std::pair<std::string, std::set<Tweet*> > > tags;
  std::map<std::string, User*> usrs;
  Tweet* tweets_;
  std::map<std::string, std::vector<Tweet*> > dmFeeds_;
  int tweetSize_;
  int tweetMaxSize_;
  Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> trending_;
  std::map<std::string, TagData> trendingNum_;


  //Functions
  User* findUser(std::string name);
  void adduser(std::string name, unsigned int hash);
  //Checks all following sets for users and adds
  //necessary users to followers
  void setallfollowers();
  std::set<Tweet*> bsearch(std::string key);
  std::string toLower(std::string in);
  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /*Outputs Tarjan's Algorithm for 
   *the users in this engine
   *@return a vector of vectors, where each inner vector is a SCC
   */
  std::vector<std::vector<User*> > tarjans();

  /*
   * Helper function for Tarjan's Algorithm
   * scc = output vector, v = current iterator in map, index = current index
   * tarMap = graph, tarSet = set, tarStack = stack
   */
  void tarH(std::vector<std::vector<User*> >& scc, 
    std::map<User*, std::pair<int, int> >::iterator v, 
    int& index, std::map<User*, std::pair<int, int> >& tarMap, 
    std::set<User*>& tarSet, std::stack<User*>& tarStack);

  /*
   * hashes a string to an unsigned int for the password
   */
  unsigned int hashPass(std::string password);
};
#endif
