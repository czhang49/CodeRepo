/**
 * @file stack.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_STACK_H_
#define CS225_STACK_H_

#include "circ_array.h"

namespace cs225
{

/**
 * Class that represents the stack (LIFO) ordering structure. This stack
 * uses an array-based implementation.
 */
template <class T>
class stack
{
  public:
    /**
     * @return the element at the top of the stack (const ref)
     */
    const T& top() const;

    /**
     * @return the element at the top of the stack (non-const ref)
     */
    T& top();

    /**
     * @param elem The element to be put on the top of the stack
     */
    void push(const T& elem);

    /**
     * @param elem The element to be put on the top of the stack (by move
     * assignment).
     */
    void push(T&& elem);

    /**
     * Remove the element that is currently on the top of the stack.
     */
    void pop();

    /**
     * @return the number of elements on the stack
     */
    uint64_t size() const;

    /**
     * @return whether the stack is empty
     */
    bool empty() const;

  private:
    /**
     * Storage for the stack's elements
     */
    circ_array<T> arr_;
};
}
#include "stack.tcc"
#endif
