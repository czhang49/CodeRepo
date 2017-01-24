/**
 * @file vertex_labels.h
 * Declaration of a vertex labeling graph feature.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_VERTEX_LABELS_H_
#define CS225_VERTEX_LABELS_H_

#include "graph.h"

namespace cs225
{

/**
 * Represents a labeling of the vertices in a graph. This is designed to be
 * used as a feature of one of the graph classes, e.g.:
 *
 * \code
 * using namespace cs225;
 * graph<vertex_labels<std:string>> g; // use vertex_labels as a graph feature
 * auto vtx = g.add_vertex();
 * g.vertex_label(vtx, "Urbana");    // sets the label for a vertex
 * auto label = g.vertex_label(vtx); // gets the label for a vertex
 * \endcode
 */
template <class T>
class vertex_labels
{
  public:
    using vertex_label_type = T;

    /**
     * @param v The vertex
     * @return the label for the given vertex (by non-const reference)
     */
    T& vertex_label(vertex v);

    /**
     * @param v The vertex
     * @return the label for the given vertex (by const reference)
     */
    const T& vertex_label(vertex v) const;

    /**
     * Sets the label for a given vertex.
     * @param v The vertex
     * @param lbl The label for that vertex
     */
    void vertex_label(vertex v, T lbl);

    /**
     * Callback for when a vertex is removed from the graph. We handle this
     * callback and remove any label associated with the given vertex.
     *
     * @param v The vertex that was removed
     */
    void remove_vertex(vertex v);

    /**
     * Callback for when an edge is removed from the graph. We ignore this
     * callback as we do not care about the edges.
     */
    void remove_edge(edge);

  private:
    /**
     * Storage for the vertex labels.
     */
    vertex_map<T> labels_;
};
}
#include "features/vertex_labels.tcc"
#endif
