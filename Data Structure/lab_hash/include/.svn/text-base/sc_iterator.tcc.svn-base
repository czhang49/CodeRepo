/** @cond STAFF */
/**
 * @file sciterator.cpp
 * Implementation of the iterator class for sc_hash_table.
 *
 * @author Chase Geigle
 * @date Summer 2012
 * @date Summer 2014
 */
/** @endcond */

#include "sc_iterator.h"

namespace cs225
{

template <class K, class V>
sc_hash_table<K, V>::iterator::iterator(
    const sc_hash_table<K, V>& ht, uint64_t idx, bool en)
    : table_{&ht}, idx_{idx}, end_{en}
{
    if (idx_ < table_->size_)
    {
        bucket_iterator_ = table_->table_[idx_].begin();
        if (bucket_iterator_ == table_->table_[idx_].end())
            increment();
    }
}

template <class K, class V>
void sc_hash_table<K, V>::iterator::increment()
{
    if (++bucket_iterator_ == table_->table_[idx_].end())
    {
        while (++idx_ < table_->size_ && table_->table_[idx_].empty())
            ;
        if (idx_ < table_->size_)
        {
            bucket_iterator_ = table_->table_[idx_].begin();
        }
        else
        {
            end_ = true;
        }
    }
}

template <class K, class V>
bool sc_hash_table<K, V>::iterator::equal(const iterator& rhs) const
{
    return table_ == rhs.table_ && idx_ == rhs.idx_ &&
           (bucket_iterator_ == rhs.bucket_iterator_ || (end_ && rhs.end_));
}

template <class K, class V>
const std::pair<K, V>& sc_hash_table<K, V>::iterator::dereference() const
{
    return *bucket_iterator_;
}

}
