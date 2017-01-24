#ifndef LPITERATOR_H_
#define LPITERATOR_H_
/** @cond STAFF */

#include <iterator>

#include "iterator_base.h"
#include "lp_hash_table.h"

/**
 * @file lp_iterator.h
 * Definition of the lp_hash_table iterator implementation.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

namespace cs225
{

/**
 * iterator implementation for lp_hash_table
 *
 * @author Chase Geigle
 * @date Summer 2012
 * @date Summer 2014
 */
template <class K, class V>
class lp_hash_table<K, V>::iterator
    : public iterator_base<std::forward_iterator_tag, std::pair<K, V>, iterator>
{
  public:
    /**
     * We friend the lp_hash_table class so that it may construct
     * iterator implementations with our private constructor.
     */
    friend class lp_hash_table<K, V>;

    // inherited functions
    void increment();
    bool equal(const iterator& other) const;
    const std::pair<K, V>& dereference() const;

  private:
    /**
     * The current bucket we are at in the lp_hash_table's internal
     * array.
     */
    uint64_t idx_;

    /**
     * Reference to the lp_hash_table we are iterating over.
     */
    const lp_hash_table* table_;

    /**
     * Private constructor: takes a lp_hash_table to iterate over and a
     * bucket index to start at.
     *
     * @param ht The lp_hash_table this iterator is going to be for.
     * @param i The bucket to start at.
     */
    iterator(const lp_hash_table& ht, uint64_t i);
};
}
/** @endcond */
#include "lp_iterator.tcc"
#endif
