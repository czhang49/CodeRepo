#ifndef SCITERATOR_H_
#define SCITERATOR_H_
/** @cond STAFF */

#include <iterator>

#include "iterator_base.h"
#include "sc_hash_table.h"

/**
 * @file sc_iterator.h
 * Definition of the sc_hash_table iterator implementation.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

namespace cs225
{

/**
 * iterator implementation for sc_hash_table
 *
 * @author Chase Geigle
 * @date Summer 2012
 * @date Summer 2014
 */
template <class K, class V>
class sc_hash_table<K, V>::iterator
    : public iterator_base<std::forward_iterator_tag, std::pair<K, V>, iterator>
{
  public:
    /**
     * We friend the sc_hash_table class so that it may construct
     * iterator implementations with our private constructor.
     */
    friend class sc_hash_table<K, V>;

    // inherited functions
    void increment();
    bool equal(const iterator& other) const;
    const std::pair<K, V>& dereference() const;

  private:
    /**
     * Reference to the table we are iterating over.
     */
    const sc_hash_table* table_;

    /**
     * Current bucket we are visiting.
     */
    uint64_t idx_;

    /**
     * Iterator over the lists in a given bucket.
     */
    typename sc_hash_table::bucket::iterator bucket_iterator_;

    /**
     * Hacky way of keeping track that we are at the end of the table.
     */
    bool end_;

    /**
     * Private constructor: takes a sc_hash_table to iterate over, an
     * integer for the bucket to start at, and a boolean indicating
     * whether we are at the end of the sc_hash_table or not.
     *
     * @param ht The sc_hash_table this iterator is going to be for.
     * @param i The bucket to start at.
     * @param ed Whether we are at the end of the sc_hash_table or not.
     */
    iterator(const sc_hash_table& ht, uint64_t idx, bool ed);
};
}
/** @endcond */
#include "sc_iterator.tcc"
#endif
