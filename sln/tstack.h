#pragma once

#include <iostream>
#include <stdexcept>

const int MAX_STACK_SIZE = 100000;

template<class T>
class TStack
{
protected:
    T** data;
    int len;
    bool isNew;
    int top;
public:
    TStack();
    TStack(int len_);
    TStack(const TStack& s);
    TStack(TStack&& s);
    TStack(T** data_, int len_);
    ~TStack();
    int GetLen();
    int GetCount();
    void Resize(int newSize);
    void SetData(T** data_, int len_);

    void Push(T elem);
    T Pop();
    TStack& operator=(const TStack& s);
    TStack& operator=(TStack&& s);
    bool operator==(const TStack& s) const;
    bool operator!=(const TStack& s) const;
    bool IsFull() const;
    bool IsEmpty() const;

    template <class O>
    friend std::ostream& operator<<(std::ostream& o, TStack<O> t);
    template <class I>
    friend std::istream& operator>>(std::istream& i, TStack<I> t);
};

template<class T>
inline TStack<T>::TStack()
{
    len = 0;
    data = nullptr;
    isNew = true;
    top = 0;
}

template<class T>
inline TStack<T>::TStack(int len_) : TStack<T>::TStack()
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
        throw std::exception();
    else if (len_ > 0)
    {
        len = len_;
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            data[i] = nullptr;
        }
    }
}

template<class T>
inline TStack<T>::TStack(const TStack& s) : TStack<T>::TStack()
{


    if (s.len > 0)
    {
        len = s.len;
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    top = s.top;
}

template<class T>
inline TStack<T>::TStack(TStack&& s)
{
    len = s.len;
    data = s.data;
    isNew = s.isNew;
    top = s.top;
    s.len = 0;
    s.data = nullptr;
    s.isNew = true;
    s.top = 0;
}

template<class T>
inline TStack<T>::TStack(T** data_, int len_) : TStack<T>::TStack()
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (len_ > 0)
    {
        len = len_;
        data = data_;
        isNew = false;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == nullptr)
            {
                top = i;
                break;
            }
        }
    }
}

template<class T>
inline TStack<T>::~TStack()
{
    if (isNew)
    {
        if (data != nullptr)
        {
            for (int i = 0; i < len; i++)
            {
                if (data[i] != nullptr)
                {
                    delete data[i];
                    data[i] = nullptr;
                }
            }
            delete[] data;
        }
    }
    data = nullptr;
    isNew = true;
    len = 0;
}

template<class T>
inline int TStack<T>::GetLen()
{
    return len;
}

template<class T>
inline int TStack<T>::GetCount()
{
    return top;
}


template<class T>
inline void TStack<T>::Resize(int newSize)
{
    if (newSize < 0 || newSize > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (newSize == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
    }
    else if (len == newSize)
    {
        return;
    }
    else
    {
        T** newData = new T * [newSize];
        for (int i = 0; i < newSize; i++)
        {
            if (i < len)
            {
                newData[i] = data[i];
            }
            else
            {
                newData[i] = nullptr;
            }
        }
        if (isNew)
        {
            delete[] data;
        }
        data = newData;
        len = newSize;
        isNew = true;
    }
}

template<class T>
inline void TStack<T>::SetData(T** data_, int len_)
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (len_ == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
    }
    else if (len_ > 0)
    {
        if (isNew)
        {
            for (int i = 0; i < len; i++)
            {
                delete data[i];
            }
            delete[] data;
        }
        data = nullptr;
        data = data_;
        len = len_;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == nullptr)
            {
                top = i;
                break;
            }
        }
    }
}

template<class T>
inline void TStack<T>::Push(T elem)
{
    if (IsFull())
    {
        throw std::exception();
    }
    data[top] = new T(elem);
    top++;
}

template<class T>
inline T TStack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::exception();
    }
    top--;
    T res = *(data[top]);
    delete data[top];
    data[top] = nullptr;
    return res;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack& s)
{
    if (this == &s)
    {
        return *this;
    }

    if (isNew && data != nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            delete data[i];
        }
        delete[] data;
    }

    len = s.len;
    top = s.top;
    isNew = true;

    if (s.len > 0)
    {
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    else
    {
        data = nullptr;
    }

    return *this;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack&& s)
{
    if (this == &s)
    {
        return *this;
    }

    if (isNew && data != nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            delete data[i];
        }
        delete[] data;
    }

    len = s.len;
    data = s.data;
    isNew = s.isNew;
    top = s.top;

    s.len = 0;
    s.data = nullptr;
    s.isNew = true;
    s.top = 0;

    return *this;
}

template<class T>
inline bool TStack<T>::operator==(const TStack& s) const
{
    if (this == &s)
    {
        return true;
    }

    if (len != s.len || top != s.top)
    {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (data[i] == nullptr && s.data[i] == nullptr)
        {
            continue;
        }
        if (data[i] == nullptr || s.data[i] == nullptr)
        {
            return false;
        }
        if (*(data[i]) != *(s.data[i]))
        {
            return false;
        }

    }
    return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack& s) const
{
    return !(*this == s);
}

template<class T>
inline bool TStack<T>::IsFull() const
{
    return top >= len;
}

template<class T>
inline bool TStack<T>::IsEmpty() const
{
    return top == 0;
}

template<class O>
inline std::ostream& operator<<(std::ostream& o, TStack<O> s)
{
    o << '(';
    for (int i = 0; i < s.len; i++)
    {
        if (s.data[i] != nullptr)
        {
            o << *(s.data[i]);
        }
        else
        {
            o << "null";
        }
        if (i == s.len - 1)
        {
            o << ')';
        }
        else
        {
            o << ' ';
        }
    }
    return o;
}

template<class I>
inline std::istream& operator>>(std::istream& i, TStack<I> t)
{
    return i;
}