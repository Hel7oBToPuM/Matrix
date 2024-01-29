#pragma once

template<class TempClass>
class List
{
    virtual size_t size() = 0;

    virtual void erase(size_t pos) = 0;

    virtual void insert(size_t pos, const TempClass& value) = 0;

    virtual void push_back(const TempClass& value) = 0;
};

