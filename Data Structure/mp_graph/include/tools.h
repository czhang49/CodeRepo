/**
 * @file tools.h
 * Declaration of utility functions on graphs. (These will be written for
 * mp_graph.2).
 */

#ifndef CS225_GRAPH_TOOLS_H_
#define CS225_GRAPH_TOOLS_H_

#include <cstdint>

#include "graph.h"

namespace cs225
{

/**
 * This namespace contains utility functions that operate on graphs. You
 * will write the implementation of these functions in mp_graph.2.
 */
namespace tools
{

/**
 * Represents the state of an edge in a traversal algorithm.
 */
enum class edge_state
{
    /// Represents an edge that is unexplored
    UNEXPLORED,
    /// Represents an edge on the spanning tree for either BFS or DFS
    DISCOVERY,
    /// Represents an edge not in the spanning tree for a DFS
    BACK,
    /// Represents an edge not in the spanning tree for a BFS
    CROSS,
    /// Special state for highlighting the minimum weighted edge
    MIN,
    /// Special state for highlighting the shortest path
    MINPATH,
    /// Special state for highlighting the edges in minimal spanning tree
    MST
};

/**
 * Represents the state of a vertex in a traversal algorithm.
 */
enum class vertex_state
{
    /// Represents a vertex that is unexplored
    UNEXPLORED,
    /// Represents a vertex that is visited
    VISITED
};

/**
 * Finds the minimum edge weight in the Graph g.
 *
 * @param g The graph to search
 * @return the weight of the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  tools::save_png() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially mark vertices and edges as unexplored using a vertex_map
 * and an edge_map.
 */
template <class Graph>
typename Graph::edge_weight_type min_weight_edge(Graph& g);

/**
 * Returns the shortest distance (in edges) between the vertices start and
 * end.
 *
 * @param g The graph to search
 * @param start The vertex to start the search from
 * @param end The vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges, not edge
 * weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use a vertex_map  but it is possible to solve this
 * problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
template <class Graph>
uint64_t shortest_path_length(Graph& g, vertex start, vertex end);

/**
 * Marks a minimum spanning tree in a graph.
 *
 * @param g The graph to find a MST for
 *
 * @todo Label the edges of a minimal spanning tree as "MST" in the graph.
 * They will appear blue when tools::save_png() is called.
 *
 * @note Use the minimum_spanning_tree helper function!
 */
template <class Graph>
void mark_mst(Graph& g);

/**
 * Finds a minimum spanning tree in a graph.
 *
 * @param g The graph to find a MST for
 * @return An edge_set indicating the edges in the MST.
 *
 * @note Use your disjoint sets class from mp_graph.1 to help you with
 * Kruskal's algorithm.
 */
template <class Graph>
edge_set minimum_spanning_tree(const Graph& g);

}
}

#include "tools.tcc"
#endif
