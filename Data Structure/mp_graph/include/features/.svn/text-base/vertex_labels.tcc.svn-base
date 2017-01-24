/**
 * @file vertex_labels.tcc
 * Definition of an vertex labeling graph feature.
 *
 * @author Chase Geigle
 * @date Sumer 2014
 */

#include "features/vertex_labels.h"

namespace cs225
{

template <class T>
T& vertex_labels<T>::vertex_label(vertex v)
{
    auto it = labels_.find(v);
    if (it == labels_.end())
        throw std::out_of_range{"vertex is unlabeled"};
    return it->second;
}

template <class T>
const T& vertex_labels<T>::vertex_label(vertex v) const
{
    auto it = labels_.find(v);
    if (it == labels_.end())
        throw std::out_of_range{"vertex is unlabeled"};
    return it->second;
}

template <class T>
void vertex_labels<T>::vertex_label(vertex v, T lbl)
{
    labels_[v] = std::move(lbl);
}

template <class T>
void vertex_labels<T>::remove_vertex(vertex v)
{
    labels_.erase(v);
}

template <class T>
void vertex_labels<T>::remove_edge(edge)
{
    // nothing
}
}
