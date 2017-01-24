/**
 * @file vertex.h
 * Definition of a vertex class.
 */

#ifndef CS225_VERTEX_H_
#define CS225_VERTEX_H_

#include <cstdint>

#include "util/identifiers.h"

namespace cs225
{
/**
 * Represents a single vertex in a graph. This is a "strong typdef",
 * meaning that it is basically just a `uint64_t`, with the exception that
 * they cannot be implicitly converted from `uint64_t`s.
 */
struct vertex : public meta::util::numerical_identifier<vertex, uint64_t>
{
    /// Inherit the constructors from our base class
    using meta::util::numerical_identifier<vertex,
                                           uint64_t>::numerical_identifier;
    /// Inherit the assignment operators from our base class
    using meta::util::numerical_identifier<vertex, uint64_t>::operator=;
};
}

namespace std
{
template <>
struct hash<cs225::vertex>
{
    size_t operator()(const cs225::vertex&) const;
};
}
#endif
