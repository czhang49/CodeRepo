/**
 * @file hashes.h
 * Definition of a namespace containing a templatized hash function.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#ifndef HASH_H_
#define HASH_H_

#include <cstdint>

/**
 * hashes namespace: a collection of templated hash functions.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
namespace hashes
{
/**
 * Computes the hash code of a given key (templated), and returns it
 * modulo size for use in HashTable applications. This function
 * **must** be specialized in order for one of SCHashTable or
 * LPHashTable to contain keys of the specialized type.
 *
 * @param key The key to be hashes.
 * @param size What to modulo the hashcode by.
 * @return The hashcode, modulo size for use as a HashTable index.
 */
template <class K>
uint64_t hash(const K& key, uint64_t size);
}
#endif
