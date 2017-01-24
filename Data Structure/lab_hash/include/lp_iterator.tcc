/** @cond STAFF */
/**
 * @file lp_iterator.tcc
 * Implementation of the iterator class for lp_hash_table.
 *
 * @author Chase Geigle
 * @date Summer 2012
 * @date Summer 2014
 */
/** @endcond */

#include "lp_iterator.h"

namespace cs225
{

template <class K, class V>
lp_hash_table<K, V>::iterator::iterator(const lp_hash_table& ht, uint64_t j)
    : idx_{j}, table_{&ht}
{
    if (idx_ < table_->size_ && table_->states_[idx_] != occupancy::OCCUPIED)
        increment();
}

template <class K, class V>
void lp_hash_table<K, V>::iterator::increment()
{
    while (++idx_ < table_->size_ &&
           table_->states_[idx_] != occupancy::OCCUPIED)
        ;
}

template <class K, class V>
bool lp_hash_table<K, V>::iterator::equal(const iterator& rhs) const
{
    return table_ == rhs.table_ && idx_ == rhs.idx_;
}

template <class K, class V>
const std::pair<K, V>& lp_hash_table<K, V>::iterator::dereference() const
{
    return table_->table_[idx_];
}
}
