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
void TStack<T>::SetData(T** data_, int len_)
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
        throw std::exception();

    if (isNew && data != nullptr)
    {
        for (int i = 0; i < len; i++)
            delete data[i];
        delete[] data;
    }

    data = data_;
    len = len_;
    isNew = false;

    top = 0;
    for (int i = 0; i < len; i++)
    {
        if (data[i] != nullptr)
            top = i + 1;
        else
            break;
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

const int MAX_MULTISTACK_SIZE = 100000;

template<class T>
class TMultiStack
{
protected:
    T** data;
    int size;
    TStack<T>* stacks;
    int stackCount;
    int* stackStarts;
    void Repack(int curStack);
public:
    TMultiStack();
    TMultiStack(int size_, int stackCount_);
    TMultiStack(const TMultiStack& ms);
    TMultiStack(TMultiStack&& ms);
    ~TMultiStack();
    int GetSize();

    void Push(T elem, int i);
    T Pop(int i);

    bool IsFull(int i) const;
    bool IsEmpty(int i) const;

    TStack<T>& operator [](int i);
};

template<class T>
void TMultiStack<T>::Repack(int curStack)
{
    int* newStart = new int[stackCount];
    int* newSizes = new int[stackCount];
    int busy = 0;
    for (int i = 0; i < stackCount; i++)
        busy += stacks[i].GetCount();
    int freeCells = size - busy;
    int ns = freeCells / stackCount;
    int tail = freeCells % stackCount;

    newStart[0] = 0;
    newSizes[0] = stacks[0].GetCount() + ns + (0 == curStack ? tail : 0);

    for (int i = 1; i < stackCount; i++)
    {
        newSizes[i] = stacks[i].GetCount() + ns + (i == curStack ? tail : 0);
        newStart[i] = newStart[i - 1] + newSizes[i - 1];
    }

    T** tempData = new T * [size];
    for (int i = 0; i < size; i++)
        tempData[i] = nullptr;

    for (int i = 0; i < stackCount; i++)
    {
        for (int j = 0; j < stacks[i].GetCount(); j++)
        {
            int oldIndex = stackStarts[i] + j;
            int newIndex = newStart[i] + j;
            if (data[oldIndex] != nullptr)
            {
                tempData[newIndex] = new T(*(data[oldIndex]));
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        delete data[i];
        data[i] = tempData[i];
    }

    delete[] tempData;

    for (int i = 0; i < stackCount; i++)
    {
        stackStarts[i] = newStart[i];
        stacks[i].SetData(&(data[newStart[i]]), newSizes[i]);
    }

    delete[] newStart;
    delete[] newSizes;
}

template<class T>
inline TMultiStack<T>::TMultiStack()
{
    data = nullptr;
    size = 0;
    stacks = nullptr;
    stackCount = 0;
    stackStarts = nullptr;
}

template<class T>
inline TMultiStack<T>::TMultiStack(int size_, int stackCount_)
{
    if (size_ < 0 || size_ > MAX_MULTISTACK_SIZE || stackCount_ < 0)
        throw std::exception();
    else if (size_ == 0 || stackCount_ == 0)
        TMultiStack<T>::TMultiStack();
    else
    {
        size = size_;
        stackCount = stackCount_;
        data = new T * [size];
        for (int j = 0; j < size; j++)
            data[j] = nullptr;
        stackStarts = new int [stackCount];
        stackStarts[0] = 0;
        int stackSize = int(size / stackCount);
        for (int i = 1; i < stackCount; i++)
            stackStarts[i] = stackStarts[i-1] + stackSize;
        stacks = new TStack<T>[stackCount];
        for (int i = 0; i < stackCount-1; i++)
            stacks[i].SetData(data + stackStarts[i], stackSize);
        stacks[stackCount - 1].SetData(data + stackStarts[stackCount - 1], stackSize + (size - stackCount* stackSize));
    }
}

template<class T>
TMultiStack<T>::TMultiStack(const TMultiStack& ms)
{
    if (ms.size == 0 || ms.stackCount == 0)
    {
        data = nullptr;
        size = 0;
        stacks = nullptr;
        stackCount = 0;
        stackStarts = nullptr;
    }
    else
    {
        size = ms.size;
        stackCount = ms.stackCount;
        data = new T * [size];

        for (int j = 0; j < size; j++)
        {
            if (ms.data[j] != nullptr)
                data[j] = new T(*(ms.data[j]));
            else
                data[j] = nullptr;
        }

        stackStarts = new int[stackCount];
        for (int i = 0; i < stackCount; i++)
            stackStarts[i] = ms.stackStarts[i];

        stacks = new TStack<T>[stackCount];
        for (int i = 0; i < stackCount; i++)
            stacks[i] = ms.stacks[i];
    }
}

template<class T>
inline TMultiStack<T>::TMultiStack(TMultiStack&& ms)
{
    data = ms.data;
    size = ms.size;
    stacks = ms.stacks;
    stackCount = ms.stackCount;
    stackStarts = ms.stackStarts;

    ms.data = nullptr;
    ms.size = 0;
    ms.stacks = nullptr;
    ms.stackCount = 0;
    ms.stackStarts = nullptr;
}

template<class T>
TMultiStack<T>::~TMultiStack()
{
    if (data != nullptr)
    {
        for (int j = 0; j < size; j++)
            delete data[j];
        delete[] data;
    }
    
    if (stacks != nullptr)
        delete[] stacks;
        
    if (stackStarts != nullptr)
        delete[] stackStarts;
}

template<class T>
inline int TMultiStack<T>::GetSize()
{
    return size;
}

template<class T>
inline void TMultiStack<T>::Push(T elem, int i)
{
    if (i < 0 || i >= stackCount)
        throw std::exception();
    if (stacks == nullptr)
        throw std::exception();
    if (stacks[i].IsFull())
        Repack(i);
    stacks[i].Push(elem);
}

template<class T>
inline T TMultiStack<T>::Pop(int i)
{
    if (i < 0 || i >= stackCount)
        throw std::exception();
    if (stacks == nullptr)
        throw std::exception();
    return stacks[i].Pop();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) const
{
    if (i < 0 || i >= stackCount)
        throw std::exception();
    if (stacks == nullptr)
        throw std::exception();
    return stacks[i].IsFull();
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int i) const
{
    if (i < 0 || i >= stackCount)
        throw std::exception();
    if (stacks == nullptr)
        throw std::exception();
    return stacks[i].IsEmpty();
}

template<class T>
inline TStack<T>& TMultiStack<T>::operator[](int i)
{
    if (i < 0 || i >= stackCount)
        throw std::exception();
    else
        return stacks[i];
}
