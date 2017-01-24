/**
 * @file queue.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_QUEUE_H_
#define CS225_QUEUE_H_

#include "circ_array.h"

namespace cs225
{

/**
 * Class that represents the queue (FIFO) ordering structure. This queue
 * uses an array-based implementation.
 */
template <class T>
class queue
{
  public:
    /**
     * @return the element at the front of the queue (const ref)
     */
    const T& front() const;

    /**
     * @return the element at the front of the queue (non-const ref)
     */
    T& front();

    /**
     * @param elem The element to be put at the back of the queue
     */
    void push(const T& elem);

    /**
     * @param elem The element to be put at the back of teh queue (by move
     * assignment).
     */
    void push(T&& elem);

    /**
     * Removes the element at the front of the queue.
     */
    void pop();

    /**
     * @return the number of elements in the queue
     */
    uint64_t size() const;

    /**
     * @return whether the queue is empty
     */
    bool empty() const;
  private:
    /// Storage for the queue's elements
    circ_array<T> arr_;
};
}
#include "queue.tcc"
#endif
