/**
 * @file sc_hash_table.tcc
 * Implementation of the sc_hash_table class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include <stdexcept>

#include "hashes.h"
#include "primes.h"
#include "sc_hash_table.h"

using hashes::hash;

namespace cs225
{

template <class K, class V>
sc_hash_table<K, V>::sc_hash_table(uint64_t tsize)
    : size_{next_prime(tsize)}, elems_{0}
{
    table_ = std::make_unique<bucket[]>(size_); // unique pointer pointees live on heap
}

template <class K, class V>
sc_hash_table<K, V>& sc_hash_table<K, V>::operator=(sc_hash_table rhs)
{
    swap(rhs);
    return *this;
}

template <class K, class V>
void sc_hash_table<K, V>::swap(sc_hash_table& other)
{
    using std::swap;
    swap(size_, other.size_);
    swap(elems_, other.elems_);
    swap(table_, other.table_);
}

template <class K, class V>
sc_hash_table<K, V>::sc_hash_table(const sc_hash_table<K, V>& other)
    : size_{other.size_}, elems_{other.elems_}
{
    table_ = std::make_unique<bucket[]>(size_);
    for (uint64_t i = 0; i < other.size_; ++i)
        table_[i] = other.table[i]; // safe! forward_list has an operator=
}

template <class K, class V>
sc_hash_table<K,V>::sc_hash_table(sc_hash_table&& other)
    : sc_hash_table{0}
{
    swap(other);
}

template <class K, class V>
void sc_hash_table<K, V>::insert(K key, V value)
{
    ++elems_;
    if (should_resize())
        resize();
    auto idx = hash(key, size_);
    table_[idx].emplace_front(std::move(key), std::move(value));
}

template <class K, class V>
void sc_hash_table<K, V>::remove(K const& key)
{
    auto idx = hash(key,size_); // your code here
    for (auto& it : table_[idx])
    {
        if (it.first == key){
		table_[idx].erase(it); // you code here
		elems_--;
		break;	// this break is essential here
	}
    }
}

template <class K, class V>
const V& sc_hash_table<K, V>::at(K const& key) const
{
    auto idx = hash(key, size_);
    for (const auto& p : table_[idx])
    {
        if (p.first == key)
            return p.second;
    }
    throw std::out_of_range{"invalid key"};
}

template <class K, class V>
V& sc_hash_table<K, V>::at(K const& key)
{
    auto idx = hash(key, size_);
    for (auto& p : table_[idx])
    {
        if (p.first == key)
            return p.second;
    }
    throw std::out_of_range{"invalid key"};
}

template <class K, class V>
V& sc_hash_table<K, V>::operator[](K const& key)
{
    auto idx = hash(key, size_);
    for (auto& p : table_[idx])
    {
        if (p.first == key)
            return p.second;
    }

    ++elems_;
    if (should_resize())
        resize();

    idx = hash(key, size_);
    table_[idx].emplace_front(key, V{});
    return table_[idx].front().second;
}

template <class K, class V>
bool sc_hash_table<K, V>::contains(K const& key) const
{
    auto idx = hash(key, size_);
    for (const auto& p : table_[idx])
    {
        if (p.first == key)
            return true;
    }
    return false;
}

template <class K, class V> //Scope & Lifetime
void sc_hash_table<K, V>::clear()
{
    size_ = next_prime(0);
    elems_ = 0;
    table_ = std::make_unique<bucket[]>(size_);
}

template <class K, class V>
void sc_hash_table<K, V>::resize()
{
    uint64_t size_prev = size_;	
    size_ = next_prime(size_);// your code here

    std::unique_ptr<bucket[]> newtable_ = std::make_unique<bucket[]>(size_);
    for (uint64_t i=0; i<size_prev; i++){
	newtable_[i] = table_[i];
    }
	
    std::swap(table_,newtable_);
    newtable_.reset(nullptr);
}

template <class K, class V>
bool sc_hash_table<K, V>::should_resize() const
{
    return (static_cast<double>(elems_) / size_) >= alpha_;
}

template <class K, class V>
bool sc_hash_table<K, V>::empty() const
{
    return elems_ == 0;
}

template <class K, class V>
uint64_t sc_hash_table<K, V>::size() const
{
    return elems_;
}

template <class K, class V>
uint64_t sc_hash_table<K, V>::table_size() const
{
    return size_;
}

template <class K, class V>
auto sc_hash_table<K, V>::begin() const -> iterator
{
    return {*this, 0, false};
}

template <class K, class V>
auto sc_hash_table<K, V>::end() const -> iterator
{
    return {*this, size_, true};
}
}
