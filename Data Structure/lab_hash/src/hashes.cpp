/**
 * @file hashes.cpp
 * Implementation of specialized hash functions for different key types.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "hashes.h"
#include <string>

namespace hashes
{
/**
 * Specialized hash() function for character keys.
 */
template <>
uint64_t hash(const char& key, uint64_t size)
{
    // simple hash, probably could be better
    return static_cast<unsigned char>(key) % size;
}

/**
 * Specialized hash() function for std::string keys.
 */
template <>
uint64_t hash(const std::string& key, uint64_t size)
{
    // Bernstein Hash
    uint64_t h = 0;
    for (size_t i = 0; i < key.length(); ++i)
        h = 33 * h + key[i];
    return h % size;
}
}
