/**
 * @file lphashtable.cpp
 * Implementation of the lp_hash_table class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include <stdexcept>

#include "hashes.h"
#include "lp_hash_table.h"
#include "primes.h"

using hashes::hash;

namespace cs225
{

template <class K, class V>
lp_hash_table<K, V>::lp_hash_table(uint64_t tsize)
    : size_{next_prime(tsize)}, elems_{0}
{
    table_ = std::make_unique<std::pair<K, V> []>(size_);
    states_ = std::make_unique<occupancy[]>(size_);
    for (uint64_t i = 0; i < size_; ++i)
        states_[i] = occupancy::UNOCCUPIED;
}

template <class K, class V>
lp_hash_table<K, V>& lp_hash_table<K, V>::operator=(lp_hash_table rhs)
{
    swap(rhs);
    return *this;
}

template <class K, class V>
lp_hash_table<K, V>::lp_hash_table(const lp_hash_table<K, V>& other)
    : size_{other.size_}, elems_{other.elems_}
{
    table_ = std::make_unique<std::pair<K, V> []>(size_);
    states_ = std::make_unique<occupancy[]>(size_);
    for (uint64_t i = 0; i < size_; ++i)
    {
        states_[i] = other.states_[i];
        if (states_[i] == occupancy::OCCUPIED)
            table_[i] = other.table_[i];
    }
}

template <class K, class V>
lp_hash_table<K, V>::lp_hash_table(lp_hash_table&& other)
    : lp_hash_table{0}
{
    swap(other);
}

template <class K, class V>
void lp_hash_table<K, V>::swap(lp_hash_table& other)
{
    using std::swap;
    swap(size_, other.size_);
    swap(elems_, other.elems_);
    swap(table_, other.table_);
    swap(states_, other.states_);
}

template <class K, class V>
void lp_hash_table<K, V>::insert(K key, V value)
{
    // your code here
	using std::move;
	using std::make_pair;
	uint64_t idx = hash(key,size_);
	for (; idx < size_ ; idx++){
	
		if (states_[idx] == occupancy::UNOCCUPIED || states_[idx] == occupancy::REMOVED){
			table_[idx] = make_pair(move(key),move(value));
			states_[idx] =  occupancy::OCCUPIED;
			break; // this break is essential
		}
	}
	
}

template <class K, class V>
void lp_hash_table<K, V>::remove(K const& key)
{
    auto idx = find_index(key);
    if (idx != -1)
    {
        --elems_;
        states_[idx] = occupancy::REMOVED;
    }
}

template <class K, class V>
int64_t lp_hash_table<K, V>::find_index(const K& key) const
{
    uint64_t idx = hash(key, size_);
    auto start = idx;
    while (states_[idx] != occupancy::UNOCCUPIED)
    {
        if (states_[idx] == occupancy::OCCUPIED && table_[idx].first == key)
            return idx;
        idx = (idx + 1) % size_;
        // if we've looped all the way around, the key has not been found
        if (idx == start)
            break;
    }
    return -1;
}

template <class K, class V>
const V& lp_hash_table<K, V>::at(K const& key) const
{
    auto idx = find_index(key);
    if (idx != -1)
        return table_[idx].second;
    throw std::out_of_range{"invalid key"};
}

template <class K, class V>
V& lp_hash_table<K, V>::at(K const& key)
{
    auto idx = find_index(key);
    if (idx != -1)
        return table_[idx].second;
    throw std::out_of_range{"invalid key"};
}

template <class K, class V>
V& lp_hash_table<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    auto idx = find_index(key);
    if (idx == -1)
    {
        // otherwise, insert the default value and return it
        insert(key, V{});
        idx = find_index(key);
    }
    return table_[idx].second;
}

template <class K, class V>
bool lp_hash_table<K, V>::contains(K const& key) const
{
    return find_index(key) != -1;
}

template <class K, class V>
void lp_hash_table<K, V>::clear()
{
    size_ = next_prime(0);
    elems_ = 0;
    table_ = std::make_unique<std::pair<K, V> []>(size_);
    states_ = std::make_unique<occupancy[]>(size_);

    for (uint64_t i = 0; i < size_; ++i)
        states_[i] = occupancy::UNOCCUPIED;
}

template <class K, class V>
void lp_hash_table<K, V>::resize()
{
    auto new_size = next_prime(size_ * 2);
    auto new_table = std::make_unique<std::pair<K, V> []>(new_size);
    auto new_states = std::make_unique<occupancy[]>(new_size);
    for (uint64_t i = 0; i < new_size; ++i)
        new_states[i] = occupancy::UNOCCUPIED;

    for (uint64_t i = 0; i < size_; i++)
    {
        if (states_[i] == occupancy::OCCUPIED)
        {
            auto idx = hash(table_[i].first, new_size);
            while (new_states[idx] != occupancy::UNOCCUPIED)
                idx = (idx + 1) % new_size;
            new_table[idx] = table_[i];
            new_states[idx] = occupancy::OCCUPIED;
        }
    }

    table_ = std::move(new_table);
    states_ = std::move(new_states);
    size_ = new_size;
}

template <class K, class V>
bool lp_hash_table<K, V>::should_resize() const
{
    return (static_cast<double>(elems_) / size_) >= alpha_;
}

template <class K, class V>
bool lp_hash_table<K, V>::empty() const
{
    return elems_ == 0;
}

template <class K, class V>
uint64_t lp_hash_table<K, V>::size() const
{
    return elems_;
}

template <class K, class V>
uint64_t lp_hash_table<K, V>::table_size() const
{
    return size_;
}

template <class K, class V>
auto lp_hash_table<K, V>::begin() const -> iterator
{
    return {*this, 0};
}

template <class K, class V>
auto lp_hash_table<K, V>::end() const -> iterator
{
    return {*this, size_};
}
}
