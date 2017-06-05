#include "alistint.h"
#include <cstdlib>
#include <stdexcept>

AListInt::AListInt()
{
    size_ = 0;
    maxsize_ = 10;
    arr_ = new int[10];
}

AListInt::AListInt(int cap)
{
    size_ = 0;
    maxsize_ = cap;
    arr_ = new int[cap];
}

AListInt::~AListInt()
{
    delete [] arr_;
}

int AListInt::size() const
{
    return size_;
}

bool AListInt::empty() const
{
    if(size_ == 0)
        return true;
    else
        return false;
}

void AListInt::insert(int pos, const int& val)
{
    if(pos < 0 || pos >size_)
    {
        return;
    }
    if(size_ + 1 >= maxsize_)
        resize();
    for(int i = size_; i > pos; i--)
    {
        arr_[i] = arr_[i-1];
    }
    arr_[pos] = val;
    size_++;
}

void AListInt::remove(int pos)
{
    if(pos < 0 || pos >= size_)
    {
        return;
    }
    for(int i = pos; i < size_-1; i++)
    {
        arr_[i] = arr_[i+1];
    }
    size_--;
    arr_[size_] = -1;
}

void AListInt::set(int position, const int& val)
{
    arr_[position] = val;
}

int& AListInt::get(int position)
{
    if(position < 0 || position >= size_)
        throw std::invalid_argument("bad location");
    return arr_[position];
}

int const & AListInt::get(int position) const
{
    if(position < 0 || position >= size_)
        throw std::invalid_argument("bad location");
    return arr_[position];
}

void AListInt::resize()
{
    int * newarr = new int[maxsize_*2];
    for(int i = 0; i < size_; i++)
    {
        newarr[i] = arr_[i];
    }
    delete [] arr_;
    arr_ = newarr;
    maxsize_ = maxsize_*2;
}
