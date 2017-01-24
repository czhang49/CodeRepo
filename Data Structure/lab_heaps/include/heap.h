/**
 * @file heap.h
 * Definition of a heap class.
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

// forward declare descriptor (used for printing, ignore)
template <class Type, class Comp>
class HeapNodeDescriptor;

/**
 * heap: A priority queue implemented as a heap.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
template <class T, class Compare = std::less<T>>
class heap
{
  public:
    /**
     * Constructs an empty heap.
     */
    heap();

    /**
     * Constructs a heap from a vector of elements by copying the
     * elements into the heap's storage and then running the buildHeap
     * algorithm.
     *
     * @param elems The elements that should be placed in the heap.
     */
    heap(const std::vector<T>& elems);

    /**
     * Removes the element with highest priority according to the
     * higher_priority() functor.
     *
     * By default, the higher_priority() function behaves like
     * operator<, so if T = int and a = 3 and b = 5, higher_priority(a,
     * b) is true (a compares smaller than b, thus it has higher
     * priority) and higher_priority(b, a) is false (b does not compare
     * smaller than a, and thus it has lower priority).
     *
     * @return The element with highest priority in the heap.
     */
    void pop();

    /**
     * Returns, but does not remove, the element with highest priority.
     *
     * @return The highest priority element in the entire heap.
     */
    const T& peek() const;

    /**
     * Inserts the given element into the heap, restoring the heap
     * property after the insert as appropriate.
     *
     * @param elem The element to be inserted.
     */
    void push(T elem);

    /**
     * Determines if the given heap is empty.
     *
     * @return Whether or not there are elements in the heap.
     */
    bool empty() const;

    /**
     * Prints the heap to an ostream. Given for you. Uses the helper
     * functions below to do its work, so please implement them!
     *
     * @param out The stream to be written to.
     * @param toPrint The heap to be printed.
     */
    template <class Type, class Comp>
    friend std::ostream& operator<<(std::ostream& out,
                                    const heap<Type, Comp>& toPrint);

    // friend descriptor to allow it to access private members
    friend class HeapNodeDescriptor<T, Compare>;

  private:
    /**
     * The internal storage for this heap. **You may choose whether
     * your heap is 0-based or 1-based (i.e., you are free to store the
     * root at either index 0 or index 1).** You should **pick *one***, and
     * write the helper functions according to that choice.
     */
    std::vector<T> elems_;

    /**
     * Comparison functor.
     */
    Compare higher_priority_;

    /**
     * Helper function that returns the root index of this heap.
     * Required for grading purposes! (This function should be
     * ridiculously easy: either return 0 if you plan to store the root
     * at index 0, or 1 if you plan on storing it at index 1).
     *
     * @return The index of the root node of the heap.
     */
    size_t root() const;

    /**
     * Helper function that returns the index of the left child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param idx The index of the current node.
     * @return The index of the left child of the current node.
     */
    size_t left_child(size_t idx) const;

    /**
     * Helper function that returns the index of the right child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param idx The index of the current node.
     * @return The index of the right child of the current node.
     */
    size_t right_child(size_t idx) const;

    /**
     * Helper function that returns the index of the parent of a node
     * in the heap.
     *
     * @param idx The index of the current node.
     * @return The index of the parent of the current node.
     */
    size_t parent(size_t idx) const;

    /**
     * Helper function that determines whether a given node has a
     * child.
     *
     * @param idx The index of the current node.
     * @return A boolean indicating whether the current node has a
     *  child or not.
     */
    bool has_child(size_t idx) const;

    /**
     * Helper function that returns the index of the child with the
     * highest priority as defined by the higher_priority() functor.
     *
     * For example, if T == int and the left child of the current node
     * has data 5 and the right child of the current node has data 9,
     * this function should return the index of the left child (because
     * the default higher_priority() behaves like operator<).
     *
     * This function assumes that the current node has children.
     *
     * @param idx The index of the current node.
     * @return The index of the highest priority child of this node.
     */
    size_t max_priority_child(size_t idx) const;

    /**
     * Helper function that restores the heap property by sinking a
     * node down the tree as necessary.
     *
     * @param idx The index of the current node that is being
     *  sunk down the tree.
     */
    void heapify_down(size_t idx);

    /**
     * Helper function that restores the heap property by bubbling a
     * node up the tree as necessary.
     *
     * @param idx The index of the current node that is being
     *  bubbled up the tree.
     */
    void heapify_up(size_t idx);
};

#include "heap.tcc"
#include "printheap.tcc"

#endif
