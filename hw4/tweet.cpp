#include "tweet.h"

Tweet::Tweet()
{}

Tweet::Tweet(std::string usrname, User* user, DateTime& time, std::string& text)
{
  usrname_ = usrname;
  user_ = user;
  time_ = time;
  text_ = text;
  setTags();
}

DateTime const & Tweet::time() const
{ return time_; }

std::string const & Tweet::text() const
{ return text_; }

std::set<std::string> Tweet::hashTags() const
{ return tags_; }

User* Tweet::user() const
{ return user_; }

bool Tweet::operator<(const Tweet& other) const
{ return(time_<other.time_); }

std::ostream& operator<<(std::ostream& os, const Tweet& t)
{
  os<<t.time_<<" " << t.usrname_ << " "<< t.text_;
  return os;
}

void Tweet::setTags()
{
  int n = 0;
  n = text_.find("#");
  while(n!=-1)
  {
    int sp = text_.find(" ", n);
    tags_.insert(text_.substr(n+1, sp-n-1));
    n = text_.find("#", n+1);
  }
}
