/**
 * @file sc_hash_table.h
 * Definition of the sc_hash_table class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 * @date Summer 2014
 */
#ifndef SCHASHTABLE_H_
#define SCHASHTABLE_H_

#include <cstdint>
#include <list>
#include <memory>

namespace cs225
{
/**
 * sc_hash_table: A hash table implementation that uses a separate chaining
 * collision resolution strategy.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <class K, class V>
class sc_hash_table
{
  public:
    class iterator;
    friend iterator;

    /**
     * Constructs a sc_hash_table of the given size.
     *
     * @param tsize The desired number of starting cells in the
     * sc_hash_table.
     */
    sc_hash_table(uint64_t tsize);

    /**
     * Destructor for the sc_hash_table.
     */
    ~sc_hash_table() = default;

    /**
     * Assignment operator.
     *
     * @param rhs The sc_hash_table we want to assign into the current one.
     * @return A reference to the current sc_hash_table.
     */
    sc_hash_table<K, V>& operator=(sc_hash_table<K, V> rhs);

    /**
     * Copy constructor.
     *
     * @param other The sc_hash_table to be copied.
     */
    sc_hash_table(const sc_hash_table<K, V>& other);

    /**
     * Move constructor.
     *
     * @param other The sc_hash_table to be moved into this one.
     */
    sc_hash_table(sc_hash_table&& other);

    /**
     * Swaps the current hash table with the parameter.
     *
     * @param other The sc_hash_table to swap with.
     */
    void swap(sc_hash_table& other);

    /**
     * Inserts the given (key, value) pair into the table.
     *
     * @param key The key to be inserted.
     * @param value The value to be inserted.
     */
    void insert(K key, V value);

    /**
     * Removes the given key (and its associated data) from the
     * hash_table.
     *
     * @param key The key to be removed.
     */
    void remove(const K& key);

    /**
     * Finds the value associated with a given key.
     *
     * @param key The key whose data we want to find.
     * @return the value associated with this key
     * @throw std::out_of_range if the key is not found
     */
    V& at(const K& key);

    /**
     * Finds the value associated with a given key. const version.
     *
     * @param key The key whose data we want to find.
     * @return the value associated with this key
     * @throw std::out_of_range if the key is not found
     */
    const V& at(const K& key) const;

    /**
     * Access operator: Returns a reference to a value in the hash table,
     * so that it may be modified. If the key you are searching for is not
     * found in the table, this method inserts it with the default value
     * V{} (which you then may modify).
     *
     * Examples:
     *
     * \code
     * hashtable["mykey"]; // returns the value for "mykey", or the
     *                     // default value if "mykey" is not in
     *                     // the table
     *
     * hashtable["myOtherKey"] = "myNewValue";
     * \endcode
     *
     * @param key The key to be found in the hash_table.
     * @return A reference to the value for this key contained in the
     * table.
     */
    V& operator[](const K& key);

    /**
     * Determines if the given key exists in the hash table.
     *
     * @param key The key we want to find.
     * @return a boolean value indicating whether the key was found in
     * the hash_table.
     */
    bool contains(const K& key) const;

    /**
     * Empties the hash table (that is, all keys and values are removed).
     */
    void clear();

    /**
     * @return whether or not the hash table is empty
     */
    bool empty() const;

    /**
     * @return the current number of elements in the hash table
     */
    uint64_t size() const;

    /**
     * @return the current size of the underlying array
     */
    uint64_t table_size() const;

    /**
     * @return an iterator to the beginning of the hash table.
     */
    iterator begin() const;

    /**
     * Returns an iterator to the end of the hash table. Note that this
     * is essentially like returning an index to one past the final
     * element in an array (that is, end() itself gives an iterator to
     * one past the last thing in the hash_table).
     *
     * @return an iterator to the end of the hash table.
     */
    iterator end() const;

  private:
    /**
     * @return whether the hash table should resize
     */
    bool should_resize() const;

    /**
     * Private helper function to resize the hash_table. This should be
     * called when `should_resize()` is true.
     */
    void resize();

    /**
     * The (constant) load factor for the hash table.
     */
    const double alpha_ = 0.7;

    /**
     * The number of buckets in the table.
     */
    uint64_t size_;

    /**
     * The number of occupants in the table.
     */
    uint64_t elems_;

    /**
     * Our bucket type is a standard doubly-linked list of pairs of (key,
     * value).
     */
    using bucket = std::list<std::pair<K, V>>;

    /**
     * Storage for our sc_hash_table.
     *
     * This is slightly ugly, but this is a dynamic array of standard
     * doubly-linked lists for the separate chaining strategy. The element
     * inside each list is a standard pair of K (key) and V (value).
     */
    std::unique_ptr<bucket[]> table_;
};
}
#include "sc_iterator.h"
#include "sc_hash_table.tcc"
#endif
