#ifndef TWITENG_H
#define TWITENG_H
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
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();

  /* You may add other member functions */

  std::vector<std::string> getUserNames();

  std::vector<std::string> getFollowing(std::string usr);

  const std::vector<Tweet*> & getDMFeed(std::string name);

   private:
  std::vector<std::pair<std::string, std::set<Tweet*> > > tags;
  std::map<std::string, User*> usrs;
  std::map<std::string, std::vector<Tweet*> > dmFeeds_;
  Tweet* tweets_;
  int tweetSize_;
  int tweetMaxSize_;

  User* findUser(std::string name);
  void adduser(std::string name);
  void follows(std::string usr, std::string usr2);
  void setallfollowers();
  std::set<Tweet*> bsearch(std::string key);
  std::string toUpper(std::string in);

};
#endif
