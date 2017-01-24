/**
 * @file premade_graphs.h
 *
 * This file builds three example graphs with the Graph library.
 * The examples have real weights between cities in miles.
 * Unfortunately, graphviz draws the nodes with a best-fit algorithm,
 *  so relative locations of cities are wrong.
 * These graphs are also used in *_test.cpp.
 * Updated by Sean Massung for Spring 2012
 *
 * @author Sean Massung
 * @date Spring 2011
 */

#ifndef PREMADE_GRAPHS_
#define PREMADE_GRAPHS_

#include <string>

#include "features/edge_labels.h"
#include "features/edge_weights.h"
#include "features/vertex_labels.h"
#include "graph.h"
#include "tools.h"

namespace cs225
{

/**
 * This namespace contains code that builds three example graphs
 *  with the Graph library. The examples have real weights between
 *  cities in miles. Unfortunately, graphviz draws the nodes with a
 *  best-fit algorithm, so relative locations of cities are wrong.
 */
namespace premade_graphs
{

using labeled_graph =
    graph<vertex_labels<std::string>, edge_labels<tools::edge_state>>;
using weighted_graph = graph<vertex_labels<std::string>,
                             edge_labels<tools::edge_state>, edge_weights<int>>;

/**
 * Returns a starting vertex for a path algorithm.
 * @param mapType - determines which map to get a starting vertex
 *  from. Possible values are "us", "europe", and "japan"
 * @return the starting vertex for a particular graph
 */
inline vertex start_vertex(std::string mapType);

/**
 * Returns a ending vertex for a path algorithm.
 * @param mapType - determines which map to get a ending vertex
 *  from. Possible values are "us", "europe", and "japan"
 * @return the ending vertex for a particular graph
 */
inline vertex end_vertex(std::string mapType);

/**
 * Creates a map of some US cities. If the specified graph type is a
 * weighted graph, distances between cities in miles are added.
 * @return the graph of a few cities in the United States
 */
template <class Graph>
Graph create_us_map();

/**
 * Creates a map of some European cities. If the specified graph type is a
 * weighted graph, distances between cities in miles are added.
 * @return the graph of a few cities in Europe
 */
template <class Graph>
Graph create_europe_map();

/**
 * Creates a map of some Japanese cities. If the specified graph type is a
 * weighted graph, distances between cities in miles are added.
 * @return the graph of a few cities in Japan
 */
template <class Graph>
Graph create_japan_map();
}
}
#include "premade_graphs.tcc"
#endif
