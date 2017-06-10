#include "setstr.h"

SetStr::SetStr()
{
    curr_ = -1;
}

SetStr::~SetStr()
{
}

int SetStr::size() const
{
    return list_.size();
}

bool SetStr::empty() const
{
    return list_.empty();
}

void SetStr::insert(const std::string& val)
{
    if(exists(val)) //duplicates
        return;
    list_.push_back(val);
    curr_=-1; //reset counter for next()
}

void SetStr::remove(const std::string&val)
{
    if(!exists(val))
        return;
    for(int i = 0; i < list_.size(); i++)
    {
        if(val.compare(list_.get(i)) == 0)
        {
            list_.remove(i);
            curr_=-1;
            return;
        }
    }
}

bool SetStr::exists(const std::string& val) const
{
    for(int i = 0; i < list_.size(); i++)
    {
        if(val.compare(list_.get(i)) == 0)
        return true;
    }
    return false; //end of list
}

std::string const* SetStr::first()
{
    if(size() == 0)
        return NULL;
    curr_ = 0;
    return &list_.get(0);
}

std::string const* SetStr::next()
{
    if(curr_==-1) return first();
    curr_++;
    if(curr_ >= size()) //end of list
    {
        curr_ = -1; //reset pointer
        return NULL;
    }
    const std::string* out = &list_.get(curr_);
    return out;
}

SetStr SetStr::setUnion(const SetStr& other) const
{
    SetStr out = *this;
    SetStr tmp = other; //copy bc other is const
    const std::string* ptr = tmp.first();
    while(ptr != NULL)
    {
        out.insert(*ptr);
        ptr = tmp.next();
    }
    return out;
}

SetStr SetStr::setIntersection(const SetStr& other) const
{
    SetStr out;
    const std::string * ptr;
    SetStr tmp = other; //copy because this is const
    ptr = tmp.first();
    while(ptr!=NULL)
    {
        if(exists(*ptr))
            out.insert(*ptr);
        ptr = tmp.next();
    }
    return out;
}

SetStr SetStr::operator|(const SetStr& other) const
{
    return setIntersection(other);
}

SetStr SetStr::operator&(const SetStr& other) const
{
    return setUnion(other);
}
