/**
 * @file edge_labels.h
 * Declaration of an edge labeling graph feature.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_EDGE_LABELS_H_
#define CS225_EDGE_LABELS_H_

#include "graph.h"

namespace cs225
{

/**
 * Represents a labeling of the edges in a graph. This is designed to be
 * used as a feature of one of the graph classes, e.g.:
 *
 * \code
 * using namespace cs225;
 * graph<edge_labels<std::string>> g; // use edge_labels as a graph feature
 * auto src = g.add_vertex();
 * auto dest = g.add_vertex();
 * auto edge = g.add_edge(src, dest);
 * g.edge_label(edge, "road");      // sets the label for an edge
 * auto label = g.edge_label(edge); // gets the label for an edge
 * \endcode
 */
template <class T>
class edge_labels
{
  public:
    using edge_label_type = T;

    /**
     * @param e The edge
     * @throw std::out_of_range if the requested edge is unlabeled
     * @return the label for the given edge (by non-const reference)
     */
    T& edge_label(edge e);

    /**
     * @param e The edge
     * @throw std::out_of_range if the requested edge is unlabeled
     * @return the label for the given edge (by const reference)
     */
    const T& edge_label(edge e) const;

    /**
     * @param u One end of the edge
     * @param v The other end of the edge
     * @throw std::out_of_range if the requested edge is unlabeled
     * @return the label for the given edge (by non-const reference)
     */
    T& edge_label(vertex u, vertex v);

    /**
     * @param u One end of the edge
     * @param v The other end of the edge
     * @throw std::out_of_range if the requested edge is unlabeled
     * @return the label for the given edge (by non-const reference)
     */
    const T& edge_label(vertex u, vertex v) const;

    /**
     * Sets the label for a given edge.
     * @param e The edge
     * @param lbl The label for that edge
     */
    void edge_label(edge e, const T& lbl);

    /**
     * Sets the label for a given edge.
     * @param u One end of the edge
     * @param v The other end of the edge
     * @param lbl The label for that edge
     */
    void edge_label(vertex u, vertex v, const T& lbl);

    /**
     * Callback for when a vertex is removed from the graph. We ignore this
     * callback, and instead only listen for when an edge is removed.
     */
    void remove_vertex(vertex);

    /**
     * Callback for when an edge is removed from the graph. We handle this
     * callback and remove any labels associated with that edge.
     *
     * @param e The edge that was removed
     */
    void remove_edge(edge e);

  private:
    /**
     * Storage for the edge labels.
     */
    edge_map<T> labels_;
};
};
#include "features/edge_labels.tcc"
#endif
