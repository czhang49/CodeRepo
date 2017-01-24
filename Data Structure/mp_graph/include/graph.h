/**
 * @file graph.h
 * Declaration for the graph class.
 *
 * Written for CS 225 Spring 2011.
 *
 * @author Sean Massung
 * @author Abigail Steitz
 * @author Chase Geigle
 *
 * Updated Spring 2012 by Sean Massung
 *  - Added doxygen comments
 *  - Created better error handling
 *  - More encapsulated and object-oriented
 *
 * Updated Summer 2014 by Abigail Steitz
 *  - Changed functions to operate more on Edges
 *  - Improved random maze generation
 *
 *  Updated Summer 2014 by Chase Geigle
 *   - Stylistic changes (C++14)
 *   - Make labels and weights be optional features, added via template
 *     parameters
 *   - Actually throw an exception for error cases instead of manually
 *     segfaulting
 *   - Refactor into a graph<GraphFeatures...> setup, where optional
 *     features are added to the graph via template parameters (e.g.,
 *     weights and labels)
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "vertex.h"
#include "edge.h"

namespace cs225
{

/**
 * A hash table that maps edges to values of any type. (A
 * typedef---provided for convenience.)
 */
template <class Value>
using edge_map = std::unordered_map<edge, Value>;

/**
 * A hash table that maps vertices to values of any type. (A
 * typedef---provided for convenience.)
 */
template <class Value>
using vertex_map = std::unordered_map<vertex, Value>;

/**
 * A hash set of edges.
 */
using edge_set = std::unordered_set<edge>;

/**
 * A hash set of vertices.
 */
using vertex_set = std::unordered_set<vertex>;

template <class... GraphFeatures>
class graph : public GraphFeatures...
{
  public:
    /**
     * Constructor to create an empty graph.
     */
    graph() = default;

    /**
     * Constructor to create a random, connected graph.
     *  No matter the density, the graph will have at least the number
     *  of edges needed to be connected.
     * @param num_vertices The number of vertices the graph will have
     * @param density The percentage density of edges in the graph.
     *                ex: 0 no edges, 50 half the possible edges, 100 all edges
     * @param seed A random seed to create the graph with
     */
    graph(uint64_t num_vertices, uint8_t density, uint64_t seed);

    /**
     * Returns one vertex in the graph. This function can be used to find a
     * vertex in the graph to start a traversal from.
     * @return a vertex from the graph
     */
    vertex start_vertex() const;

    /**
     * @return all of the vertices of this graph, as a set
     */
    vertex_set vertices() const;

    /**
     * @return all of the edges of this graph, as a set
     */
    edge_set edges() const;

    /**
     * @param v The vertex in question
     * @return all adjacent vertices to the parameter, as a set
     */
    const vertex_set& adjacent(vertex v) const;

    /**
     * Adds a new vertex to the graph.
     * @return the vertex inserted
     */
    vertex add_vertex();

    /**
     * Removes a vertex from the graph.
     * @param v The vertex to remove
     */
    void remove_vertex(vertex v);

    /**
     * Adds a new edge to the graph.
     * @param u The source of the edge
     * @param v The destination of the edge
     * @return a copy of the edge added
     */
    edge add_edge(vertex u, vertex v);

    /**
     * Removes an edge from the graph.
     * @param u The source of the edge
     * @param v The destination of the edge
     */
    void remove_edge(vertex u, vertex v);

    /**
     * Removes an edge from the graph.
     * @param e The edge
     */
    void remove_edge(edge e);

    /**
     * @param u One vertex
     * @param v Another vertex
     * @return whether or not u has an edge connecting it to v
     */
    bool has_edge(vertex u, vertex v) const;

    /**
     * Exception class for graph operations.
     */
    struct exception : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

  private:

    /**
     * Checks whether a vertex exists in the graph.
     * @param v The vertex to check for existence
     * @throw exception if the vertex is not part of the graph
     */
    void assert_exists(vertex v) const;

    /**
     * Checks whether an edge exists between two vertices in the graph.
     * @param u One vertex
     * @param v The other vertex
     * @throw exception if the edge is not part of the graph
     */
    void assert_exists(vertex u, vertex v) const;

    /**
     * Internal representation for the graph: a map from vertex sets of
     * vertices (adjacency sets).
     */
    vertex_map<std::unordered_set<vertex>> adjacency_sets_;

    /**
     * The next valid vertex in the graph.
     */
    vertex next_vertex_{0};
};
}

#include "graph.tcc"
#endif
