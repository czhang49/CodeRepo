/**
 * @file demo.cpp
 *
 * This file shows how the Graph class can be used.
 * Feel free to play around in this area!
 *
 * @author Sean Massung
 * @date Spring 2011
 *
 * Updated by Sean Massung for Spring 2012
 */

#include <iostream>
#include <string>

#include "features/edge_labels.h"
#include "features/edge_weights.h"
#include "features/vertex_labels.h"
#include "graph.h"
#include "premade_graphs.h"
#include "tools_provided.h"

using std::string;
using std::cout;
using std::endl;
using namespace cs225;
using namespace premade_graphs;

/**
 * Draws the three example graphs with weights.
 * All graphs saved as PNGs are in the images/ folder.
 */
void create_premade_graphs()
{
    auto us = create_us_map<weighted_graph>();
    auto europe = create_europe_map<weighted_graph>();
    auto japan = create_japan_map<weighted_graph>();

    // save PNGs
    tools::save_png(us, "united-states-mst");
    tools::save_png(europe, "europe");
    tools::save_png(japan, "japan");

    // print to terminal
    cout << "\nDisplaying a graph of Europe...\n\n";
    tools::print(europe);
}

/**
 * Create the US map without weights.
 */
void create_unweighted_us()
{
    auto us_uw = create_us_map<labeled_graph>();
    tools::save_png(us_uw, "us-unweighted");
}

/**
 * Create and print a random weighted graph with
 *  9 vertices and random seed 777.
 */
void create_random_graph()
{
    cout << "\nDisplaying a random graph with about half the edges...\n\n";
    graph<edge_weights<int>> graph{9, 50, 777};
    std::random_device rd;
    std::mt19937 rng{rd()};
    for (const auto& e : graph.edges())
        graph.edge_weight(e, rng());
    tools::print(graph);
    tools::save_png(graph, "random-graph-demo");
}

/**
 * Build a graph by manually inserting vertices.
 */
void build_graph()
{
    cout << "Displaying a manually created graph...\n\n";
    graph<vertex_labels<std::string>, edge_labels<std::string>,
          edge_weights<int>> graph;

    // Use snapshot feature
    auto snapshot = tools::snapshot{"demo_build_graph_"};

    // Getting vertices and setting labels
    auto a = graph.add_vertex();
    graph.vertex_label(a, "A");
    auto b = graph.add_vertex();
    graph.vertex_label(b, "B");
    auto c = graph.add_vertex();
    graph.vertex_label(c, "C");

    // Getting vertices
    auto ab = graph.add_edge(a, b);
    (void) ab; // silence unused variable warning
    auto ac = graph.add_edge(a, c);
    graph.add_edge(b, c);
    edge bc{b, c};

    // Setting edge weights (have corresponding get methods)
    graph.edge_weight(a, b, 7); // with vertices
    graph.edge_weight(ac, 11);  // with edge
    int acWeight = graph.edge_weight(ac);
    graph.edge_weight(bc, acWeight + 1);
    snapshot(graph);

    // Edge labels
    graph.edge_label(a, b, "DISCOVERY");
    graph.edge_label(ac, "CROSS");
    snapshot(graph);

    tools::save_png(graph, "built-graph");
    tools::print(graph);
}

/**
 * Run all the different examples.
 */
int main()
{
    create_premade_graphs();
    create_unweighted_us();
    create_random_graph();
    build_graph();
    return 0;
}
