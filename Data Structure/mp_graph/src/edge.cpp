/**
 * @file edge.cpp
 * Implementation details for the edge class.
 */

#include <functional>

#include "edge.h"

namespace cs225
{

edge edge::reverse() const
{
    return {dest, source};
}

bool operator==(const edge& lhs, const edge& rhs)
{
    return lhs.source == rhs.source && lhs.dest == rhs.dest;
}
}

namespace
{
/// @see boost.hash_combine
template <class T>
inline void hash_combine(size_t& seed, const T& v)
{
    auto h = std::hash<T>{};
    seed ^= h(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
}

namespace std
{
size_t hash<cs225::edge>::operator()(const cs225::edge& e) const
{
    size_t seed = 0;
    hash_combine<uint64_t>(seed, e.source);
    hash_combine<uint64_t>(seed, e.dest);
    return seed;
}
}
