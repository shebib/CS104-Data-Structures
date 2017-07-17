#include "twiteng.h"

TwitEng::TwitEng() : trending_(2)
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

void TwitEng::adduser(std::string name, unsigned int hash)
{
  User* usr = new User(name, hash);
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

std::string TwitEng::toLower(std::string in)
{
  std::string out;
    for(unsigned int i = 0; i < in.length(); i++)
    {
      out += std::tolower(in[i]);
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
    std::string tag = toLower(*it);
    bool inserted = false;
    for(unsigned int i = 0; i < tags.size(); i++)
    {
      if(tags[i].first.compare(tag) == 0)
      {
        tags[i].second.insert(tmp);
        inserted = true;
        //increase count in map and heap
        int pnum = trendingNum_.find(tag)->second.num;
        trendingNum_.find(tag)->second.num++;
        trending_.decreaseKey(TagData(tag, pnum), trendingNum_.find(tag)->second);
      }
      else if(tags[i].first.compare(tag) < 0)
      {
        std::set<Tweet*> newset;
        newset.insert(tmp);
        tags.insert(tags.begin()+i, std::make_pair(tag, newset));
        inserted = true;
        //add to map and heap
        trendingNum_.insert(std::make_pair(tag, TagData(tag, 1)));
        trending_.push(trendingNum_.find(tag)->second);
      }
      if(inserted)
        break;
    }
    if(!inserted)
    {
      std::set<Tweet*> newset;
      newset.insert(tmp);
      tags.push_back(std::make_pair(tag, newset));
      trendingNum_.insert(std::make_pair(tag, TagData(tag, 1)));
      trending_.push(trendingNum_.find(tag)->second);
    }
  }
  //add to DM feed
  
  if(tmp->isDM()) //add first @ to dmFeeds_
  {
    std::string dmname = tmp->text().substr(1, tmp->text().find(" ")-1);
    if(dmFeeds_.find(dmname) == dmFeeds_.end())
    {
      std::vector<Tweet*> add; 
      dmFeeds_.insert(std::make_pair(dmname, add));
    }
    dmFeeds_.find(dmname)->second.push_back(tmp);
  }
  else //add all @
  {
    int n = 0;
    n = tmp->text().find("@");
    while(n!=-1)
    {
      int sp = tmp->text().find(" ", n);
      std::string dmname = tmp->text().substr(n+1, sp-n-1);
      if(dmFeeds_.find(dmname) == dmFeeds_.end())
      {
        std::vector<Tweet*> add;
        dmFeeds_.insert(std::make_pair(dmname, add));
      }
      dmFeeds_.find(dmname)->second.push_back(tmp);
      n = tmp->text().find("@", n+1);
    }
  }
}

bool TwitEng::parse(char* filename)
{
  std::ifstream fin(filename);
   if(!fin.good()) {//check input file
     std::cout << "Error: Input file not found\n";
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
     std::string usr = "";
     unsigned int hash = 0;
     ss >> usr;
     ss >> hash;
     adduser(usr, hash);
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
     unsigned int hash = 0;
     ss >> hash;
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
  key = toLower(key);
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
    for(unsigned int i = 0; i < feed.size(); i++)
    {
      fout << *feed[i] << std::endl;
    }
    fout.close();
  }
}

User* TwitEng::findUser(std::string name)
{
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    if(it->first.compare(name) == 0)
      return it->second;
  }
  throw name;
}

std::vector<std::string> TwitEng::getUserNames()
{
  std::vector<std::string> out;
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    out.push_back(it->first);
  }
  return out;
}

std::vector<std::string> TwitEng::getFollowing(std::string usr)
{
  std::vector<std::string> out;
  User* user = findUser(usr);
  std::set<User*> following = user->following();
  for(std::set<User*>::iterator it = following.begin() ; it != following.end(); it++)
  {
    out.push_back((*it)->name());
  }
  return out;
}

const std::string TwitEng::getDMFeed(std::string name)
{
  if(dmFeeds_.find(name) == dmFeeds_.end())
    return "";
  MSort<Tweet*, TweetComp>::mergeSort(dmFeeds_.find(name)->second, TweetComp());
  std::string out = "";
  std::vector<Tweet*> dmOut = dmFeeds_.find(name)->second;
  std::stringstream ss;
  for(unsigned int i = 0; i < dmOut.size(); i++)
  {
    ss << *dmOut[i] << std::endl;
    std::string tmp = "";
    while(ss >> tmp) { out+=tmp+" ";}
    out += "\n";
    ss.str("");
    ss.clear();
  }
  return out;
}

const std::string TwitEng::getFeed(std::string name)
{
  std::vector<Tweet*> feedTweets = this->findUser(name)->getFeed();
  std::string out = "";
  std::stringstream ss;
  for(unsigned int i = 0; i < feedTweets.size(); i++)
  {
    ss << *feedTweets[i] << std::endl;
    std::string tmp = "";
    while(ss >> tmp) { out+=tmp+" ";}
    out += "\n";
    ss.str("");
    ss.clear();
  }
  return out;
}

  void TwitEng::saveToFile(std::string filename)
{
  const char* fname = filename.c_str();
  std::ofstream fout(fname);
  fout << usrs.size() << std::endl;
  //output users and followings
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    fout << it->first << " ";
    std::set<User*> followings = it->second->following();
    for(std::set<User*>::iterator it2 = followings.begin(); it2 != followings.end(); it2++)
    {
      fout << (*it2)->name() << " ";
    }
    fout << "\b\n";
  }
  //output tweets
  for(int i = 0; i < tweetSize_; i++)
  {
    fout << tweets_[i] << std::endl;
  }
}

  const std::vector<std::string> TwitEng::searchTweets(std::vector<std::string>& terms, int strategy)
{
  std::vector<Tweet*> tweets = search(terms, strategy);
  std::vector<std::string> out;
  std::stringstream ss;
  for(unsigned int i = 0; i < tweets.size(); i++)
  {
    out.push_back("");
    ss << *(tweets[i]);
    std::string tmp = "";
    while(ss >> tmp) {out[i] += tmp + " ";}
    ss.str("");
    ss.clear();
  }
  return out;
}

void TwitEng::saveComponentsToFile(std::string filename)
{
  const char* fname = filename.c_str();
  std::ofstream fout(fname);
  std::vector<std::vector<User*> > scc = tarjans();
  for(unsigned int i = 0; i < scc.size(); i++)
  {
    fout << "Component " << i+1 << std::endl;
    for(unsigned int j = 0; j < scc[i].size(); j++)
    {
      fout << scc[i][j]->name() << std::endl;
    }
  }
}

std::vector<std::vector<User*> > TwitEng::tarjans()
{
  //Generate tarMap
  std::map<User*, std::pair<int, int> > tarMap;
  std::set<User*> tarSet;
  std::stack<User*> tarStack;
 
  for(std::map<std::string, User*>::iterator it = usrs.begin(); it != usrs.end(); it++)
  {
    tarMap.insert(std::make_pair(it->second, std::make_pair(-1, -1)));
  }

  int index = 0;
  std::vector<std::vector<User*> > scc;
  for(std::map<User*, std::pair<int, int> >::iterator it = tarMap.begin(); it != tarMap.end(); it++)
  {
    if(it->second.first == -1) //unvisited
    {
      tarH(scc, it, index, tarMap, tarSet, tarStack);
    }
  }

  return scc;
}

void TwitEng::tarH(std::vector<std::vector<User*> >& scc, 
    std::map<User*, std::pair<int, int> >::iterator v, 
    int& index, std::map<User*, std::pair<int, int> >& tarMap, 
    std::set<User*>& tarSet, std::stack<User*>& tarStack)
{
  v->second.first = index;
  v->second.second = index;
  index++;
  tarStack.push(v->first);
  tarSet.insert(v->first);

  for(std::set<User*>::iterator it = v->first->following().begin(); it != v->first->following().end(); it++)
  {
    std::map<User*, std::pair<int, int> >::iterator w = tarMap.find(*it);
    if(w->second.first == -1)
    {
      tarH(scc, w, index, tarMap, tarSet, tarStack);
      v->second.second = std::min(v->second.second, w->second.second);
    }
    else if(tarSet.find(w->first) != tarSet.end()) //following is on stack
    {
      v->second.second = std::min(v->second.second, w->second.first);
    }
  }

  if(v->second.second == v->second.first)
  {
    std::vector<User*> newSCC;
    std::map<User*, std::pair<int, int> >::iterator w;
    do
    {
      w = tarMap.find(tarStack.top());
      tarStack.pop();
      tarSet.erase(w->first);
      newSCC.push_back(w->first);
    } while (w->first != v->first);
    scc.push_back(newSCC);
  }
}

const std::vector<std::string> TwitEng::getTrending()
{
  int size = tags.size();
  if(size > 5)
    size = 5;
  std::vector<std::string> out;
  std::vector<TagData> tArr;
  for(int i = 0; i < size; i++)
  {
    tArr.push_back(trending_.top());
    trending_.pop();
    std::stringstream ss;
    ss << "#" << tArr[i].tag << "(" << tArr[i].num << ")";
    out.push_back(ss.str());
    ss.str("");
    ss.clear();
  }
  for(int i = 0; i < size; i++)
    trending_.push(tArr[i]);
  return out;
}
  
bool TwitEng::login(std::string username, std::string password)
{
  if(usrs.find(username) == usrs.end())
    return false;
  if(password.length() > 8)
    return false;
  User* user = usrs.find(username)->second;
  unsigned int hash = hashPass(password);
  if(user->getPass() == hash)
    return true;
  else
    return false;
}

unsigned int TwitEng::hashPass(std::string password)
{
  unsigned long long val = 0;
  unsigned int len = password.length();
  for(unsigned int i = 0; i < len; i++)
  {
    val += pow(128, len-i-1)*(int)password[i];
  }
  unsigned int wval[4];
  for(int i = 0; i < 4; i++)
  {
    if(val == 0)
    {
      for(int j = i; j < 4; j++)
      {
        wval[3-j] = 0;
      }
    }
    wval[3-i] = val % 65521;
    val = val/65521;
  }
  return ((45912*wval[0]+35511*wval[1]+65169*wval[2]+4625*wval[3])%65521);
}

bool TwitEng::registerUser(std::string username, std::string password)
{
  if(usrs.find(username) != usrs.end())
    return false;
  unsigned int hash = hashPass(password);
  adduser(username, hash);
  return true;
}
