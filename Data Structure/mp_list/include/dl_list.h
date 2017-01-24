/**
 * @file dl_list.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef DL_LIST_H_
#define DL_LIST_H_

#include <iterator>
#include <memory>
#include <ostream>

namespace cs225
{

/**
 * A data structure adhering to the List ADT, implemented internally as a
 * doubly-linked list.
 */
template <class T>
class dl_list
{
  private:
    /**
     * Represents a single node in the list. Each node has ownership of the
     * next node in the list, and has a raw "observation" pointer to the
     * previous node.
     *
     * The node data is immutable (const). (Please don't change this.)
     */
    struct node
    {
        /**
         * Constructs a new node with the given data element. The node will
         * have nullptr for both next and prev members.
         *
         * Implemented for you.
         * @see dl_list_provided.tcc
         *
         * @param elem The desired element for the new node.
         */
        node(T elem);

        /**
         * An owning pointer to the next node in the sequence. May be
         * nullptr.
         */
        std::unique_ptr<node> next;

        /**
         * An observing pointer to the previous node in the sequence. May
         * be nullptr.
         */
        node* prev;

        /**
         * The (immutable) data for this node.
         */
        const T data;
    };

  public:
    /**
     * Creates an empty list.
     */
    dl_list();

    /**
     * Copies another list.
     * @param other The list to copy
     */
    dl_list(const dl_list& other);

    /**
     * Move construction---move the parameter into the newly constructed
     * list, leaving the parameter empty.
     *
     * @param other The list to be moved
     */
    dl_list(dl_list&& other);

    /**
     * Lists may be assigned.
     * @param rhs The list to assign into the current object
     * @return a reference to the current list
     */
    dl_list& operator=(dl_list rhs);

    /**
     * Swaps the current list with another.
     * @param other The list to swap with
     */
    void swap(dl_list& other);

    /**
     * Adds an element to the back of the list.
     * @param data The desired data for the new element
     */
    void push_back(T data);

    /**
     * Adds an element to the front of the list.
     * @param data The desired data for the new element
     */
    void push_front(T data);

    /**
     * Implemented for you.
     * @see dl_list_provided.tcc
     * @return the number of elements in the list
     */
    uint64_t size() const;

    /**
     * Reverses the current list, in-place.
     */
    void reverse();

    /**
     * Reverses blocks of of a specific size in the list.
     *
     * You should use your reverse(std::unique_ptr<node>& first, node*&
     * last) helper function in this method!
     *
     * @param n The size of the blocks in the list to be reversed
     */
    void reverse_nth(unsigned n);

    /**
     * Modifies the list using the waterfall algorithm.
     *
     * Every other node (starting from the second one) is removed from the
     * list, but appended at the back, becoming the new tail. This
     * continues until the next thing to be removed is either the tail
     * (**not necessarily the original tail!**) or nullptr. You may **NOT**
     * allocate new nodes. Note that since the tail should be continuously
     * updated, some nodes will be moved more than once.
     */
    void waterfall();

    /**
     * Splits the given list into two parts.
     *
     * @param split_point The point at which to split the list, in terms
     * of elements from the head
     * @return The second list created from the split
     */
    dl_list split(unsigned split_point);

    /**
     * Merges the given sorted list into the current sorted list.
     *
     * @param to_merge A sorted dl_list to merge into the current one
     */
    void merge(dl_list& to_merge);

    /**
     * Sorts the current list in-place using the mergesort algorithm.
     */
    void sort();

// provided functions for grading (do *not* remove!)
#include "dl_list_provided.h"

  private:
    /**
     * Helper function for reversing a sequence of linked memory inside a
     * dl_list, starting at first and ending at last.
     *
     * You are responsible for updating `first` and `last` to refer to the
     * new starting and ending points, respectively. Be careful! They are
     * references!
     *
     * @param first A reference to the owning pointer for the beginning of
     * the sub-list to be reversed
     * @param last A reference to the observing pointer for the end of the
     * sub-list to be reversed
     */
    void reverse(std::unique_ptr<node>& first, node*& last);

    /**
     * Helper function to split a sequence of linked memory within a
     * dl_list at the node `split_point` steps after `start`.
     *
     * In other words, it should disconnect the sequence of linked memory
     * after the given number of nodes, and return an owning pointer to the
     * starting node of the new sequence of linked memory.
     *
     * This function should **NOT** create any new dl_list objects, nor
     * should it create any new node objects.
     *
     * @param start An observing pointer to the start of the sequence to
     * be split
     * @param split_point The number of nodes after start at which to
     * split the list (always > 0)
     */
    std::unique_ptr<node> split(node* start, unsigned split_point);

    /**
     * Helper function to merge two **sorted** and **independent**
     * sequences of linked memory.
     *
     * The result should be a single sequence that is itself sorted and has
     * all of the elements of the two sequences given.
     *
     * This function should **NOT** create any new dl_list objects, nor
     * should it create any new node objects.
     *
     * @param first An owning pointer to the first sorted sequence
     * @param second An owning pointer to the second sorted sequence
     * @return an owning pointer to the front of the merged sequence
     */
    std::unique_ptr<node> merge(std::unique_ptr<node> first,
                                std::unique_ptr<node> second);

    /**
     * Helper function for sorting a chain of linked memory that begins at
     * `start` and ends `length` nodes after it.
     *
     * This is the recursive helper function for the mergesort algorithm
     * (i.e., the divide-and-conquer step).
     *
     * This function should **NOT** create any new dl_list objects, nor
     * should it create any new node objects.
     *
     * @param start An owning pointer to the start of the sequence to be
     * sorted
     * @param length The length of the sequence to be sorted
     * @return an owning pointer to the start of the sorted sequence
     */
    std::unique_ptr<node> mergesort(std::unique_ptr<node> start,
                                    uint64_t length);

    /**
     * An owning pointer to the first node in the list.
     */
    std::unique_ptr<node> head_;

    /**
     * An observing pointer to the last node in the list.
     */
    node* tail_;

    /**
     * The number of elements in the list.
     */
    uint64_t size_;
};

/**
 * Convenience function for printing a list. Implemented for you.
 * @see dl_list_provided.tcc
 *
 * @param stream The stream to print to
 * @param lst The list to print
 * @return the stream object we are printing on
 */
template <class T>
std::ostream& operator<<(std::ostream& stream, const dl_list<T>& lst);
}

#include "dl_list.tcc"

// provided functions (do *not* remove!)
#include "dl_list_provided.tcc"
#endif
