#include "user.h"
#include <algorithm>

User::User(std::string name) 
{
  name_ = name;
}

User::~User() {}

std::string User::name() const 
{ return name_; }

std::set<User*> User::followers() const
{ return followers_; }

std::set<User*> User::following() const
{ return following_; }

std::list<Tweet*> User::tweets() const
{ return tweets_; }

void User::addFollower(User* u)
{ followers_.insert(u); }

void User::addFollowing(User* u)
{ following_.insert(u); }

void User::addTweet(Tweet* t)
{ tweets_.push_back(t); }

std::vector<Tweet*> User::getFeed()
{
  std::vector<Tweet*> out;
  for(std::list<Tweet*>::iterator it = tweets_.begin(); it != tweets_.end(); it++) //tweets
  {
    out.push_back(*it);
  }
  for(std::set<User*>::iterator it = following_.begin(); it != following_.end(); it++) //followers
  {
    std::list<Tweet*> ftweets = (*it)->tweets();
    for(std::list<Tweet*>::iterator it2 = ftweets.begin(); it2 != ftweets.end(); it2++)
    {
      out.push_back(*it2);
    }
  }
  std::sort(out.begin(), out.end()); 
  return out;
}
