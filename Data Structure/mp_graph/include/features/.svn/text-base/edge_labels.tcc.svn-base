/**
 * @file edge_labels.tcc
 * Definition of an edge labeling graph feature.
 *
 * @author Chase Geigle
 * @date Sumer 2014
 */

#include "features/edge_labels.h"

namespace cs225
{

template <class T>
T& edge_labels<T>::edge_label(edge e)
{
    auto it = labels_.find(e);
    if (it == labels_.end())
        throw std::out_of_range{"edge is unlabeled"};
    return it->second;
}

template <class T>
const T& edge_labels<T>::edge_label(edge e) const
{
    auto it = labels_.find(e);
    if (it == labels_.end())
        throw std::out_of_range{"edge is unlabeled"};
    return it->second;
}

template <class T>
T& edge_labels<T>::edge_label(vertex u, vertex v)
{
    return edge_label({u, v});
}

template <class T>
const T& edge_labels<T>::edge_label(vertex u, vertex v) const
{
    return edge_label({u, v});
}

template <class T>
void edge_labels<T>::edge_label(edge e, const T& lbl)
{
    labels_[e] = lbl;
    labels_[e.reverse()] = lbl;
}

template <class T>
void edge_labels<T>::edge_label(vertex u, vertex v, const T& lbl)
{
    edge_label({u, v}, lbl);
}

template <class T>
void edge_labels<T>::remove_vertex(vertex)
{
    // nothing
}

template <class T>
void edge_labels<T>::remove_edge(edge e)
{
    labels_.erase(e);
    labels_.erase(e.reverse());
}
}
