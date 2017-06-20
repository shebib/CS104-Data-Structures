#include "datetime.h"

DateTime::DateTime()
{
  hour = -1; 
  min = -1;
  sec = -1;
  year = -1;
  month = -1;
  day = -1;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
  hour = hh;
  min = mm;
  sec = ss;
  this->year = year;
  this->month = month;
  this->day = day;
}

bool DateTime::operator<(const DateTime& other) const
{
  if(year<other.year)
    return true;
  else if(year > other.year)
    return false;
  else
  {
    if(month<other.month)
      return true;
    else if(month > other.month)
      return false;
    else
    {
      if(day<other.day)
        return true;
      else if(day>other.day)
        return false;
      else
      {
        if(hour<other.hour)
          return true;
        else if (hour>other.hour)
          return false;
        else
          {
            if(min < other.min)
              return true;
            else if(min >other.min)
              return false;
            else
            {
              if(sec < other.sec)
                return true;
              else
                return false;
            }
          }
      }
    }
  }
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
  std::string out[6];
  std::stringstream ss;
  ss <<other.year;
  out[0] = ss.str();
  ss.str("");
  ss <<other.month;
  out[1] = ss.str();
  ss.str("");
  ss <<other.day;
  out[2] = ss.str();
  ss.str("");
  ss <<other.hour;
  out[3] = ss.str();
  ss.str("");
  ss <<other.min;
  out[4] = ss.str();
  ss.str("");
  ss <<other.sec;
  out[5] = ss.str();
  ss.str("");
  for(int i = 1; i < 6; i ++)
  {
    if(out[i].length() < 2)
      out[i] = "0" + out[i];
  }
  std::string h = "-";
  std::string s = ":";
  os<<out[0]<<h<<out[1]<<h<<out[2]<<" "<<out[3]<<s<<out[4]<<s<<out[5];
  return os;
}


std::istream& operator>>(std::istream& is, DateTime& dt)
{
  is >> dt;
  return is;
}
