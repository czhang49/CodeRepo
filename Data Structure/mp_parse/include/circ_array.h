/**
 * @file circ_array.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_CIRC_ARRAY_H_
#define CS225_CIRC_ARRAY_H_

#include <cstdint>
#include <memory>

namespace cs225
{

 /**
 * A class that implements the "circular, wrap-around array" that provides
 * efficient insertion and removal at the front and back of the array.
 */
template <class T>
class circ_array
{
  public:
    /**
     * Constructs an array with 0 capacity.
     */
    circ_array();

    /**
     * Constructs an array with the given capacity.
     *
     * @param size The desired capacity
     */
    circ_array(uint64_t size);

    /**
     * Copies another circ_array.
     *
     * @param other The array to be copied
     */
    circ_array(const circ_array& other);

    /**
     * Moves another circ_array into this one.
     *
     * @param other The array to be moved
     */
    circ_array(circ_array&& other);

    /**
     * Assignment operator
     *
     * @param rhs The element to be assigned into this array
     * @return A reference to the current array
     */
    circ_array& operator=(circ_array rhs);

    /**
     * Frees all resources associated with this array.
     */
    ~circ_array();

    /**
     * Swaps this array instance with another.
     *
     * @param other The array to swap with
     */
    void swap(circ_array& other);

    /**
     * Un-checked access operator. Indexes are from the *user perspective*
     * (meaning 0 always represents the start of the array).
     *
     * @param idx The user-perspective index into the array
     * @return a const reference to the element at that position
     */
    const T& operator[](uint64_t idx) const;

    /**
     * Un-checked access operator. Indexes are from the *user perspective*
     * (meaning 0 always represents the start of the array).
     *
     * @param idx The user-perspective index into the array
     * @return a reference to the element at that position
     */
    T& operator[](uint64_t idx);

    /**
     * Checked access operator. Indexes are from the *user perspective*
     * (meaning 0 always represents the start of the array). A
     * std::out_of_range exception should be thrown if attempting to access
     * invalid elements.
     *
     * @param idx The user-perspective index into the array
     * @return a const reference to the element at that position
     */
    const T& at(uint64_t idx) const;

    /**
     * Checked access operator. Indexes are from the *user perspective*
     * (meaning 0 always represents the start of the array). A
     * std::out_of_range exception should be thrown if attempting to access
     * invalid elements.
     *
     * @param idx The user-perspective index into the array
     * @return a const reference to the element at that position
     */
    T& at(uint64_t idx);

    /**
     * Inserts an element at the front of the array. Must run in \f$O(1)\f$
     * time.
     *
     * @param elem The element to be inserted
     */
    void push_front(const T& elem);

    /**
     * Inserts an element at the front of the array. Please use move
     * semantics for this overload! Must run in \f$O(1)\f$ time.
     *
     * @param elem The element to be inserted (via move assignment)
     */
    void push_front(T&& elem);

    /**
     * Inserts an element at the back of the array. Must run in \f$O(1)\f$
     * time.
     *
     * @param elem The element to be inserted
     */
    void push_back(const T& elem);

    /**
     * Inserts an element at the back of the array. Please use move
     * semantics for this overload! Must run in \f$O(1)\f$ time.
     *
     * @param elem The element to be inserted (via move assignment)
     */
    void push_back(T&& elem);

    /**
     * Removes the element at the front of the array. Must run in
     * \f$O(1)\f$ time.
     */
    void pop_front();

    /**
     * Removes the element at the back of the array. Must run in \f$O(1)\f$
     * time.
     */
    void pop_back();

    /**
     * Removes the element at the user-perspective index given. (Exercise:
     * what is the best running time possible for this function, and why?)
     *
     * @param idx The user-perspective index of the element to be removed.
     */
    void erase(uint64_t idx);

    /**
     * @return the number of user-specified elements in the array
     */
    uint64_t size() const;

    /**
     * @return whether the array contains any user-specified elements
     */
    bool empty() const;

  private:
    /**
     * Storage for the array.
     */
    std::unique_ptr<T[]> arr_;
	bool filled() const;
	void recapacity();
	uint64_t getindex(uint64_t idx) const;
	uint64_t capacity_;
	uint64_t head_;
	uint64_t end_;	
	uint64_t size_;
    // you probably need more members...
};
}
#include "circ_array.tcc"
#endif
