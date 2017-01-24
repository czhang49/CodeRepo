/**
 * @file edge_weights.tcc
 * Definition of an edge weight graph feature.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "features/edge_weights.h"

namespace cs225
{

template <class T>
T& edge_weights<T>::edge_weight(edge e)
{
    auto it = weights_.find(e);
    if (it == weights_.end())
        throw std::out_of_range{"edge has no weight"};
    return it->second;
}

template <class T>
const T& edge_weights<T>::edge_weight(edge e) const
{
    auto it = weights_.find(e);
    if (it == weights_.end())
        throw std::out_of_range{"edge has no weight"};
    return it->second;
}

template <class T>
T& edge_weights<T>::edge_weight(vertex u, vertex v)
{
    return edge_weight({u, v});
}

template <class T>
const T& edge_weights<T>::edge_weight(vertex u, vertex v) const
{
    return edge_weight({u, v});
}

template <class T>
void edge_weights<T>::edge_weight(edge e, T w)
{
    weights_[e] = w;
    weights_[e.reverse()] = w;
}

template <class T>
void edge_weights<T>::edge_weight(vertex u, vertex v, T w)
{
    edge_weight({u, v}, w);
}

template <class T>
void edge_weights<T>::remove_vertex(vertex)
{
    // nothing
}

template <class T>
void edge_weights<T>::remove_edge(edge e)
{
    weights_.erase(e);
    weights_.erase(e.reverse());
}
}
