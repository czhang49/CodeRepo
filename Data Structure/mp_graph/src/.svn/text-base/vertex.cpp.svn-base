/**
 * @file vertex.cpp
 * Implementation details for the vertex class.
 */

#include <functional>

#include "vertex.h"

namespace std
{
size_t hash<cs225::vertex>::operator()(const cs225::vertex& v) const
{
    auto h = std::hash<uint64_t>{};
    return h(v);
}
}
