/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#ifndef CS225_EDGE_H_
#define CS225_EDGE_H_

#include "vertex.h"

namespace cs225
{
/**
 * Represents a single edge in a graph.
 */
struct edge
{
    vertex source;
    vertex dest;

    edge reverse() const;
};

bool operator==(const edge& lhs, const edge& rhs);
}

namespace std
{
template <>
struct hash<cs225::edge>
{
    size_t operator()(const cs225::edge& e) const;
};
}
#endif
