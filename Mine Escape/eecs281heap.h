//
//  eecs281heap.h
//  Mine Escape
//
//  Created by Dimitri Tolios on 10/26/16.
//  Copyright © 2016 Dimitri Tolios. All rights reserved.
//

#ifndef EECS281_HEAP_H
#define EECS281_HEAP_H

#include <functional>
#include <iterator>
#include <vector>

//A simple interface that implements a generic heap.
//Runtime specifications assume constant time comparison and copying.
template<typename TYPE, typename COMP = std::less<TYPE>>
class eecs281heap {
public:
    typedef unsigned size_type;
    
    virtual ~eecs281heap() {}
    
    //Description: Assumes that all elements inside the heap are out of order and
    //             'rebuilds' the heap by fixing the heap invariant.
    //NOTE: This should be called between rounds after you have updated
    //      the priorities of all of the elements inside.
    //Runtime: O(n log n) - some implementations *must* have tighter bounds (see
    //         specialized headers).
    virtual void make_heap() = 0;
    
    //Description: Add a new element to the heap.
    //Runtime: O(n) - some implementations *must* have tighter bounds (see
    //         specialized headers).
    virtual void push(const TYPE& val) = 0;
    
    //Description: Remove the most extreme (defined by 'compare') element from
    //             the heap.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the heap is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: O(n) - some implementations *must* have tighter bounds (see
    //         specialized headers).
    virtual void pop() = 0;
    
    //Description: Return the most extreme (defined by 'compare') element of
    //             the heap.
    //Runtime: O(n) - some implementations *must* have tighter bounds (see
    //         specialized headers).
    virtual const TYPE& top() const = 0;
    
    //Description: Get the number of elements in the heap.
    //Runtime: O(1)
    virtual size_type size() const = 0;
    
    //Description: Return true if the heap is empty.
    //Runtime: O(1)
    virtual bool empty() const = 0;
    
protected:
    //Note: These data members *must* be used in all of your heap
    //      implementations.
    
    //You can use this in the derived classes with:
    //this->compare(Thing1, Thing2)
    //With the default compare function (std::less), this will
    //tell you if Thing1 is less than Thing2.
    COMP compare;
};


#endif //EECS281_HEAP_H
