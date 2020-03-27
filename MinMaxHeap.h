#ifndef MINMAXHEAP_H_INCLUDED
#define MINMAXHEAP_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class MinMaxHeap
{
public:

    MinMaxHeap() :
        m_data(std::vector<T>()),
        m_size(0)
    {
    }

    MinMaxHeap(std::vector<T> data) :
        m_data(std::vector<T>(data)),
        m_size(data.size())
    {
        int mn = (m_size / 2) + 1;
        if (m_size < mn)
            mn = m_size;
        for (unsigned int i = mn; i >= 1; i--)
            PushDown(i);
    }

    void       Insert(T);
    T          GetMin();
    T          GetMax();
    T          PopMin();
    T          PopMax();

    inline int GetSize() const { return m_size; }

private:

    int              GetLayer(int);

    void             PushDown(int);
    void             PushDownMin(int);
    void             PushDownMax(int);

    void             PushUp(int);
    void             PushUpMin(int);
    void             PushUpMax(int);

    T                GetData(int);
    void             SetData(T, int);
    void             Swap(int, int);

    std::vector<int> GetNodeChildren(int);

private:

    std::vector<T> m_data;
    unsigned int   m_size;
};

template <typename T>
void MinMaxHeap<T>::Insert(T element)
{
    if (m_data.size() > m_size)
        m_data[m_size] = element;
    else
        m_data.push_back(element);

    m_size++;

    PushUp(m_size);
}

template <typename T>
T MinMaxHeap<T>::GetMin()
{
    if (m_size)
        return GetData(1);

    return T();
}

template <typename T>
T MinMaxHeap<T>::GetMax()
{
    if (m_size)
    {
        if (m_size == 1)
            return GetData(1);
        else
            if (m_size < 3)
                return GetData(2);
            else
                return std::max(GetData(2), GetData(3));
    }

    return T();
}

template <typename T>
T MinMaxHeap<T>::PopMin()
{
    if (m_size)
    {
        T result = GetData(1);

        if (m_size > 1)
        {
            SetData(GetData(m_size), 1);

            m_size--;
            PushDown(1);
        }
        else
            m_size--;

        return result;
    }

    return T();
}

template <typename T>
T MinMaxHeap<T>::PopMax()
{
    if (m_size)
    {
        if (m_size == 1)
        {
            T result = GetData(1);
            m_size--;
            return result;
        }
        else if (m_size < 3)
        {
            T result = GetData(2);
            m_size--;
            return result;
        }
        else
        {
            int ix     = 2;
            T   result = GetData(ix);

            if (GetData(3) > result)
            {
                result = GetData(3);
                ix     = 3;
            }

            SetData(GetData(m_size), ix);
            m_size--;
            PushDown(ix);

            return result;
        }
    }

    return T();
}

template <typename T>
int MinMaxHeap<T>::GetLayer(int index)
{
    int pow = 2;
    int layer = 1;
    while (pow <= index)
    {
        pow <<= 1;
        layer++;
    }

    return layer;
}

template <typename T>
void MinMaxHeap<T>::PushDown(int index)
{
    if (GetLayer(index) % 2 != 0)
        PushDownMin(index);
    else
        PushDownMax(index);
}

template <typename T>
void MinMaxHeap<T>::PushDownMin(int index)
{
    std::vector<int> childrenIndices = GetNodeChildren(index);

    if (childrenIndices.size() != 0)
    {
        int  minIndex   = childrenIndices[0];
        bool grandChild = false;

        for (int i = 0; i < childrenIndices.size(); i++)
            if (GetData(minIndex) > GetData(childrenIndices[i]))
                minIndex = childrenIndices[i];

        for (int i = 0; i < childrenIndices.size(); i++)
        {
            std::vector<int> grandchildren = GetNodeChildren(childrenIndices[i]);
            for (int j = 0; j < grandchildren.size(); j++)
            {
                if (GetData(minIndex) > GetData(grandchildren[j]))
                {
                    minIndex   = grandchildren[j];
                    grandChild = true;
                }
            }
        }

        if (grandChild)
        {
            if (GetData(minIndex) < GetData(index))
            {
                Swap(minIndex, index);

                int parentIndex = minIndex / 2;

                if (GetData(minIndex) > GetData(parentIndex))
                    Swap(minIndex, parentIndex);

                PushDownMin(minIndex);
            }
        }
        else if (GetData(minIndex) < GetData(index))
            Swap(minIndex, index);
    }
}

template <typename T>
void MinMaxHeap<T>::PushDownMax(int index)
{
    std::vector<int> childrenIndices = GetNodeChildren(index);

    if (childrenIndices.size() != 0)
    {
        int  maxIndex   = childrenIndices[0];
        bool grandChild = false;

        for (int i = 0; i < childrenIndices.size(); i++)
            if (GetData(maxIndex) < GetData(childrenIndices[i]))
                maxIndex = childrenIndices[i];

        for (int i = 0; i < childrenIndices.size(); i++)
        {
            std::vector<int> grandchildren = GetNodeChildren(childrenIndices[i]);
            for (int j = 0; j < grandchildren.size(); j++)
            {
                if (GetData(maxIndex) < GetData(grandchildren[j]))
                {
                    maxIndex   = grandchildren[j];
                    grandChild = true;
                }
            }
        }

        if (GetData(maxIndex) > GetData(index))
        {
            Swap(maxIndex, index);

            int parentIndex = maxIndex / 2;

            if (GetData(maxIndex) < GetData(parentIndex))
                Swap(maxIndex, parentIndex);

            PushDownMin(maxIndex);
        }
        else if (GetData(maxIndex) > GetData(index))
            Swap(maxIndex, index);
    }
}

template <typename T>
void MinMaxHeap<T>::PushUp(int index)
{
    if (index != 1)
    {
        int layer  = GetLayer(index);
        int parent = index / 2;
        if (layer % 2 != 0)
        {
            if (GetData(index) > GetData(parent))
            {
                Swap(index, parent);
                PushUpMax(parent);
            }
            else
                PushUpMin(index);
        }
        else
        {
            if (GetData(index) < GetData(parent))
            {
                Swap(index, parent);
                PushUpMin(parent);
            }
            else
                PushUpMax(index);
        }
    }
}

template <typename T>
void MinMaxHeap<T>::PushUpMin(int index)
{
    int grandParent = index / 4;
    if (grandParent > 0)
    {
        if (GetData(index) < GetData(grandParent))
        {
            Swap(index, grandParent);
            PushUpMin(grandParent);
        }
    }
}

template <typename T>
void MinMaxHeap<T>::PushUpMax(int index)
{
    int grandParent = index / 4;
    if (grandParent > 0)
    {
        if (GetData(index) > GetData(grandParent))
        {
            Swap(index, grandParent);
            PushUpMax(grandParent);
        }
    }
}

template <typename T>
T MinMaxHeap<T>::GetData(int index)
{
    if (index > m_size || index < 1)
    {
        std::cout << "Can't access the index " << index << ", you idiot." << std::endl;
        std::cout << "Prepare for unexpected behaviour.. or even a crash?" << std::endl;
        return T();
    }

    return m_data[index - 1];
}

template <typename T>
void MinMaxHeap<T>::SetData(T value, int index)
{
    if (index > m_size || index < 1)
    {
        std::cout << "Can't set the value at position " << index << "." << std::endl;
        return;
    }

    m_data[index - 1] = value;
}

template <typename T>
void MinMaxHeap<T>::Swap(int index1,
                         int index2)
{
    T tmp = GetData(index1);
    SetData(GetData(index2), index1);
    SetData(tmp, index2);
}

template <typename T>
std::vector<int> MinMaxHeap<T>::GetNodeChildren(int index)
{
    std::vector<int> result;
    int leftChild = index * 2;
    if (leftChild <= m_size)
    {
        result.push_back(leftChild);
        int rightChild = (index * 2) + 1;

        if (rightChild <= m_size)
            result.push_back(rightChild);
    }

    return result;
}

#endif // MINMAXHEAP_H_INCLUDED
