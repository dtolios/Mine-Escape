//
//  binary_heap.h
//  Mine Escape
//
//  Created by Dimitri Tolios on 10/26/16.
//  Copyright © 2016 Dimitri Tolios. All rights reserved.
//

#ifndef binary_heap_h
#define binary_heap_h
#include "eecs281heap.h"
#include <algorithm>

//A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP = std::less<TYPE>>
class binary_heap : public eecs281heap<TYPE, COMP>
{
public:
    typedef unsigned size_type;
    
    //Description: Construct a heap out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    binary_heap(InputIterator start, InputIterator end, COMP comp = COMP());
    
    //Description: Construct an empty heap with an optional comparison functor.
    //Runtime: O(1)
    binary_heap(COMP comp = COMP());
    
    //Description: Assumes that all elements inside the heap are out of order and
    //             'rebuilds' the heap by fixing the heap invariant.
    //Runtime: O(n)
    virtual void make_heap();
    
    //Description: Add a new element to the heap.
    //Runtime: O(log(n))
    virtual void push(const TYPE& val);
    
    //Description: Remove the most extreme (defined by 'compare') element from
    //             the heap.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the heap is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: O(log(n))
    virtual void pop();
    
    //Description: Return the most extreme (defined by 'compare') element of
    //             the heap.
    //Runtime: O(1)
    virtual const TYPE& top() const;
    
    //Description: Get the number of elements in the heap.
    //Runtime: O(1)
    virtual size_type size() const
    {
        return data.size();
    }
    
    //Description: Return true if the heap is empty.
    //Runtime: O(1)
    virtual bool empty() const
    {
        return data.empty();
    }
private:
    //Note: This vector *must* be used your heap implementation.
    std::vector<TYPE> data;
private:
    //***Add any additional member functions or data you require here.
};

template<typename TYPE, typename COMP>
template<typename InputIterator>
binary_heap<TYPE, COMP>::binary_heap(InputIterator start,
                                     InputIterator end,
                                     COMP comp)
{
    this->compare = comp;
    for(InputIterator iterator = start; iterator != end; iterator++)
        data.push_back(*iterator);
    make_heap();
}

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP>::binary_heap(COMP comp)
{
    this->compare = comp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::make_heap()
{
    //index of the max parent (the last parent in the tree)
    unsigned int maxParentIndex = ((int)data.size() - 2)/2;
    //index for left, right, and parent nodes
    unsigned int left = 0;
    unsigned int right = 0;
    int parent = 0;
    
    for(signed int i = maxParentIndex; i >= 0; i--)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        parent = i;
        if(left < data.size() && this->compare(data[left], data[parent]))
            parent = left;
        if(right < data.size() && this->compare(data[right], data[parent]))
            parent = right;
        if(parent != i)
            std::swap(data[i], data[parent]);
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::push(const TYPE& val)
{
    data.push_back(val);
    int addedElementIndex = (int)data.size() - 1;
    int parentIndex =  (addedElementIndex - 2)/2;
    while(parentIndex >= 0 &&
          !this->compare(data[parentIndex], data[addedElementIndex]))
    {
        std::swap(data[parentIndex], data[addedElementIndex]);
        addedElementIndex = parentIndex;
        parentIndex = (addedElementIndex - 2) / 2;
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::pop()
{
    if(!data.empty())
    {
        //first swap first item with last
        std::swap(data[0], data[data.size()-1]);
        
        //remove the last item in the vector
        data.pop_back();
        //heapify
        make_heap();
    }
}

template<typename TYPE, typename COMP>
const TYPE& binary_heap<TYPE, COMP>::top() const
{
    return data.front();
}


#endif /* binary_heap_h */
