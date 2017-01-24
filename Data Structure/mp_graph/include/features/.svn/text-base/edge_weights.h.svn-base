/**
 * @file edge_weights.h
 * Declaration of an edge weight graph feature.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_EDGE_WEIGHTS_H_
#define CS225_EDGE_WEIGHTS_H_

#include <type_traits>

#include "graph.h"

namespace cs225
{

/**
 * Represents weights for the edges in a graph. This is designed to be used
 * as a feature of one of the graph classes, e.g.:
 *
 * \code
 * using namespace cs225;
 * graph<edge_weights<double>> g; // use edge_weights as a graph feature
 * auto src = g.add_vertex();
 * auto dest = g.add_vertex();
 * auto edge = g.add_edge(src, dest);
 * g.edge_weight(edge, 10.3);         // sets the label for an edge
 * auto weight = g.edge_weight(edge); // gets the label for an edge
 * \endcode
 */
template <class T>
class edge_weights
{
  public:
    // ensure that we are truly dealing with numeric weights
    static_assert(std::is_integral<T>::value ||
                      std::is_floating_point<T>::value ||
                      std::is_base_of<meta::util::numeric, T>::value,
                  "edge weights must be numeric types");

    using edge_weight_type = T;

    /**
     * @param e The edge
     * @throw std::out_of_range if the requested edge has no weight
     * @return the weight for the given edge (by non-const reference)
     */
    T& edge_weight(edge e);

    /**
     * @param e The edge
     * @throw std::out_of_range if the requested edge has no weight
     * @return the weight for the given edge (by const reference)
     */
    const T& edge_weight(edge e) const;

    /**
     * @param u One end of the edge
     * @param v The other end of the edge
     * @throw std::out_of_range if the requested edge has no weight
     * @return the weight for the given edge (by non-const reference)
     */
    T& edge_weight(vertex u, vertex v);

    /**
     * @param u One end of the edge
     * @param v The other end of the edge
     * @throw std::out_of_range if the requested edge has no weight
     * @return the weight for the given edge (by non-const reference)
     */
    const T& edge_weight(vertex u, vertex v) const;

    /**
     * Sets the weight for a given edge.
     * @param e The edge
     * @param w The weight for that edge
     */
    void edge_weight(edge e, T w);

    /**
     * Sets the weight for a given edge.
     * @param u One end of the edge
     * @param v The other end of the edge
     * @param w The weight for that edge
     */
    void edge_weight(vertex u, vertex v, T w);

    /**
     * Callback for when a vertex is removed from the graph. We ignore this
     * callback, and instead only listen for when an edge is removed.
     */
    void remove_vertex(vertex);

    /**
     * Callback for when an edge is removed from the graph. We handle this
     * callback and remove any weights associated with that edge.
     */
    void remove_edge(edge e);

  private:
    /**
     * Storage for the edge weights.
     */
    edge_map<T> weights_;
};
}

#include "features/edge_weights.tcc"
#endif
