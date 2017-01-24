/**
 * @file lp_hash_table.h
 * Definition of a Linear Probing Hash Table.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 * @date Summer 2014
 */
#ifndef LPHASHTABLE_H_
#define LPHASHTABLE_H_

#include <cstdint>
#include <memory>

namespace cs225
{
/**
 * lp_hash_table: a hash table implementation that uses linear probing as a
 * collision resolution strategy.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <class K, class V>
class lp_hash_table
{
  public:
    class iterator;
    friend iterator;

    /**
     * Constructs a lp_hash_table of the given size.
     *
     * @param tsize The desired number of starting cells in the
     *  lp_hash_table.
     */
    lp_hash_table(uint64_t tsize);

    /**
     * Destructor for the lp_hash_table.
     */
    ~lp_hash_table() = default;

    /**
     * Assignment operator.
     *
     * @param rhs The lp_hash_table we want to assign into the current
     * one.
     * @return A reference to the current lp_hash_table.
     */
    lp_hash_table<K, V>& operator=(lp_hash_table rhs);

    /**
     * Copy constructor.
     *
     * @param other The lp_hash_table to be copied.
     */
    lp_hash_table(const lp_hash_table<K, V>& other);

    /**
     * Move constructor.
     *
     * @param other The lp_hash_table to be moved into this one.
     */
    lp_hash_table(lp_hash_table<K, V>&& other);

    /**
     * Swaps the current lp_hash_table with the parameter.
     *
     * @param other The lp_hash_table to swap with.
     */
    void swap(lp_hash_table& other);

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
     * Helper function to determine the index where a given key lies in
     * the lp_hash_table. If the key does not exist in the table, it will
     * return -1.
     *
     * @param key The key to look for.
     * @return The index of this key, or -1 if it was not found.
     */
    int64_t find_index(const K& key) const;

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
     * Occupancy flags. We have three states: UNOCCUPIED, OCCUPIED, and
     * REMOVED.
     *
     * - UNOCCUPIED indicates that the cell is "free" (and has never
     *   contained an element).
     * - OCCUPIED indicates that there is currently a valid element in that
     *   cell position.
     * - REMOVED indicates that the cell is free for adding new elements,
     *   but that an element used to exist here (and thus, we must probe
     *   forward if doing another find/remove operation).
     */
    enum class occupancy
    {
        UNOCCUPIED,
        OCCUPIED,
        REMOVED
    };

    /**
     * Storage for our lp_hash_table.
     *
     * With linear probing, we only need the array, not buckets for each
     * array index.
     */
    std::unique_ptr<std::pair<K, V> []> table_;

    /**
     * Storage for the occupancy state for each cell.
     */
    std::unique_ptr<occupancy[]> states_;
};
}

#include "lp_iterator.h"
#include "lp_hash_table.tcc"
#endif
