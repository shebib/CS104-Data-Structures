#include "twiteng.h"

TwitEng::TwitEng()
{
  tweetSize_ = 0;
  tweets_ = new Tweet[10];
  tweetMaxSize_ = 10;
}
TwitEng::~TwitEng() 
{
  delete [] tweets_;
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    delete it->second;
  }
}

void TwitEng::adduser(std::string name)
{
  User* usr = new User(name);
  usrs.insert(std::make_pair(name, usr));
}

void TwitEng::follows(std::string usr, std::string usr2)
{
  usrs.find(usr)->second->addFollowing(usrs.find(usr2)->second);
  if(usrs.find(usr2) != usrs.end())
    usrs.find(usr2)->second->addFollower(usrs.find(usr)->second);
}

void TwitEng::setallfollowers()
{
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    std::set<User*> following = it->second->following();
    for(std::set<User*>::iterator itu = following.begin(); itu != following.end(); itu++)
    {
      (*itu)->addFollower(it->second);
    }
  }
}

std::string TwitEng::toUpper(std::string in)
{
  std::string out;
    for(unsigned int i = 0; i < in.length(); i++)
    {
      out += std::toupper(in[i]);
    }
    return out;
}

void TwitEng::addTweet(std::string& username, DateTime& dt, std::string& text)
{
  if(usrs.find(username) == usrs.end())
    throw username;
  User* usr = usrs.find(username)->second;
  if(tweetSize_ == tweetMaxSize_)
  {
    Tweet* tmp = tweets_;
    tweets_ = new Tweet[tweetMaxSize_*2];
    for(int i = 0; i < tweetSize_; i++)
    {
      tweets_[i] = tmp[i];
    }
    tweetMaxSize_ = tweetMaxSize_*2;
  }
  Tweet* tmp = new Tweet(username, usr, dt, text);
  tweets_[tweetSize_] = *tmp; 
  tweetSize_++;

  usr->addTweet(tweets_+tweetSize_-1);

  //Add hashtags
  std::set<std::string> newtags = tmp->hashTags();
  for(std::set<std::string>::iterator it = newtags.begin(); it != newtags.end(); it++)
  {
    std::string tag = toUpper(*it);
    bool inserted = false;
    for(unsigned int i = 0; i < tags.size(); i++)
    {
      if(tags[i].first.compare(tag) == 0)
      {
        tags[i].second.insert(tmp);
        inserted = true;
      }
      else if(tags[i].first.compare(tag) < 0)
      {
        std::set<Tweet*> newset;
        newset.insert(tmp);
        tags.insert(tags.begin()+i, std::make_pair(tag, newset));
        inserted = true;
      }
      if(inserted)
        break;
    }
    if(!inserted)
    {
      std::set<Tweet*> newset;
      newset.insert(tmp);
      tags.push_back(std::make_pair(tag, newset));
    }
  }
}

bool TwitEng::parse(char* filename)
{
  std::ifstream fin(filename);
   if(!fin.good()) {//check input file
     std::cout << "Error: Input file not found";
       return true;
   }
   std::stringstream ss;
   std::string tmp;
   std::getline(fin, tmp);
   ss.str(tmp);
   int num = 0;
   ss >> num;
   for(int i = 0; i < num; i++)
   {
     std::getline(fin, tmp);
     ss.flush();
     ss.clear();
     ss.str(tmp);
     std::string usr;
     ss >> usr;
     adduser(usr);
     std::string follow;
     while(ss >>follow)
     {
       //follows(usr, follow);
       //Do this again later once we ahve all users
     }
   }
  //do that again to add all folloewrs/followings properly
  //this took me aprox one year to figure out
   std::ifstream fin2(filename);
   std::getline(fin2, tmp);
   for(int i = 0; i < num; i++)
   {
     std::getline(fin2, tmp);
     ss.flush();
     ss.clear();
     ss.str(tmp);
     std::string usr;
     ss >> usr;
     std::string follow;
     while(ss >>follow)
     {
       follows(usr, follow);
     }
   }

   while(!fin.eof())
   {
     std::getline(fin, tmp);
     if(tmp.empty())
       break;
     std::string ins[6];
     ins[0] = tmp.substr(0, 4);
     ins[1] = tmp.substr(5, 2);
     ins[2] = tmp.substr(8, 2);
     ins[3] = tmp.substr(11, 2);
     ins[4] = tmp.substr(14, 2);
     ins[5] = tmp.substr(17, 2);
     int intin[6];
     for(int i = 0; i < 6; i++)
     {
       ss.flush();
       ss.clear();
       ss.str(ins[i]);
       ss >> intin[i];
     }
     int yyyy = intin[0]; 
     int mm = intin[1];
     int dd = intin[2];
     int hh = intin[3];
     int min = intin[4];
     int ss = intin[5];
     int sp = tmp.find(" ", 20);
     std::string username = tmp.substr(20, sp-20);
     std::string text = tmp.substr(sp+1);
     DateTime dt(hh, min, ss, yyyy, mm, dd);
     addTweet(username, dt, text);
   }
   setallfollowers();
   return false;
}

std::set<Tweet*> TwitEng::bsearch(std::string key)
{
  key = toUpper(key);
  int l = 0;
  int r = tags.size() - 1;
  while(!(l>r))
  {
    int m = (l+r)/2;
    if(tags[m].first.compare(key) < 0) 
      r = m-1;
    else if(tags[m].first.compare(key) > 0)
      l = m+1;
    else
    {
      return tags[m].second;
    }
  }
  throw NULL;
}

std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
  std::vector<Tweet*> out;
  std::vector<std::set<Tweet*> > sets;
  for(unsigned int i = 0; i < terms.size(); i++)
  {
    try
    {
      sets.push_back(bsearch(terms[i]));
    }
    catch (...)
    {
      if(strategy == 0)
        return out;
    }
  }
  if(strategy == 0)
  {
    for(std::set<Tweet*>::iterator it = sets[0].begin(); it != sets[0].end(); it++)
    {
      bool exists = true;
      for(unsigned int i = 0; i < sets.size(); i++)
      {
        if(sets[i].find(*it) == sets[i].end())
          exists = false;
      }
      if (exists)
        out.push_back(*it);
    }
  }
  if(strategy == 1)
  {
    std::set<Tweet*> sout;
    for(unsigned int i = 0; i < sets.size(); i++)
    {
      for(std::set<Tweet*>::iterator it = sets[i].begin(); it != sets[i].end(); it++)
      {
        sout.insert(*it);
      }
    }
    for(std::set<Tweet*>::iterator it = sout.begin(); it != sout.end(); it++)
    {
      out.push_back(*it);
    }
  }
  return out;
}

void TwitEng::dumpFeeds()
{
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    std::string filename = it->first;
    filename = filename + ".feed";
    const char* fname = filename.c_str();
    std::ofstream fout(fname);
    std::vector<Tweet*> feed = it->second->getFeed();
    std::sort(feed.begin(), feed.end(), TweetComp());
    for(unsigned int i = 0; i < feed.size(); i++)
    {
      fout << *feed[i] << std::endl;
    }
    fout.close();
  }
}