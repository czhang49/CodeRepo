/**
 * @file tests.cpp
 * Contains code to test the functions in tools.
 *
 * Written for CS 225 Spring 2011
 * @author Sean Massung
 *
 * Updated Spring 2012.
 * Updates Summer 2014.
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "graph.h"
#include "premade_graphs.h"
#include "tools.h"
#include "tools_provided.h"

using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;

using namespace cs225;

/**
 * Show how to use the GraphTools tester.
 * @param programName - the name to display in the usage text
 */
void error(string programName)
{
    cerr
        << "\nusage: " << programName << " testType graphType" << endl
        << "\ttestType can be \"weight\", \"path\", or \"kruskal\"" << endl
        << "\tfor map graphs, graphType can be \"us\", \"europe\", or \"japan\""
        << endl << "\tfor random graphs, graphType can be \"random\" and you "
                   "can specify" << endl
        << "\t  the number of vertices and a random seed if wanted." << endl
        << endl
        << "example: test finding minimum weight on a graph of Europe:" << endl
        << "\t" << programName << " weight europe" << endl << endl
        << "example: test minimal spanning tree on a random graph:" << endl
        << "\t" << programName << " kruskal random" << endl << endl
        << "example: test shortest path on a random graph with 8 vertices, "
           "edge density of 25 and "
           "seed 777:" << endl << "\t" << programName << " path random 8 25 777"
        << endl << endl;
}

/**
 * Tests tools::min_weight_edge.
 * @param graph - the graph to run the test on
 * @param fileName- the prefix for the filename to save the graph
 */
template <class Graph>
void testMinWeight(Graph& graph, string fileName)
{
    auto weight = tools::min_weight_edge(graph);
    tools::save_png(graph, "min-weight-" + fileName);
    tools::print(graph);
    cout << "Minimum weight: " << weight << endl;
}

/**
 * Tests tools::shortest_path_length.
 * @param graph - the graph to run the test on
 * @param start - the vertex to find a path from
 * @param end - the vertex to find a path to
 * @param fileName- the prefix for the filename to save the graph
 */
template <class Graph>
void testShortestPath(Graph& graph, vertex start, vertex end, string fileName)
{
    auto pathSize = tools::shortest_path_length(graph, start, end);
    tools::save_png(graph, "shortest-path-" + fileName);
    tools::print(graph);
    cout << "Shortest path from " << start << " to " << end << ": " << pathSize
         << (pathSize == 1 ? " edge." : " edges.") << endl;
}

/**
 * Tests GraphTools::findMST.
 * @param graph - the graph to run the test on
 * @param fileName- the prefix for the filename to save the graph
 */
template <class Graph>
void testKruskal(Graph& graph, string fileName)
{
    tools::mark_mst(graph);
    tools::save_png(graph, "kruskal-" + fileName);
    tools::print(graph);
}

template <class Graph>
Graph make_graph(const std::string& type, uint64_t num_vertices,
                 uint8_t density, uint64_t seed)
{
    if (type == "us")
        return premade_graphs::create_us_map<Graph>();
    if (type == "europe")
        return premade_graphs::create_europe_map<Graph>();
    if (type == "japan")
        return premade_graphs::create_japan_map<Graph>();
    if (type == "random")
        return {num_vertices, density, seed};
    throw std::invalid_argument{"invalid graph type"};
}

/**
 * Parses command line arguments and runs the appropriate test.
 */
int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 6)
    {
        error(argv[0]);
        return 1;
    }

    string test(argv[1]);
    string type(argv[2]);

    bool weighted = (test != "path");
    uint64_t num_vertices = 9; // default for random graphs
    uint64_t seed = 777;
    uint8_t density = 23;
    if (argc == 6)
    {
        std::istringstream{argv[3]} >> num_vertices;
        uint64_t dens;
        std::istringstream{argv[4]} >> dens;
        density = dens;
        std::istringstream{argv[5]} >> seed;
    }

    // deduce graph type
    if (weighted)
    {
        using graph_t = premade_graphs::weighted_graph;
        auto g = make_graph<graph_t>(type, num_vertices, density, seed);
        if (type == "random")
        {
            // set all edge weights to random numbers
            std::mt19937_64 rng{seed};
            for (const auto& e : g.edges())
                g.edge_weight(e, rng());
        }

        if (test == "weight")
            testMinWeight(g, type);
        else if (test == "kruskal")
            testKruskal(g, type);
        else
            throw std::invalid_argument{"invalid test type"};
    }
    else
    {
        using graph_t = premade_graphs::labeled_graph;
        auto g = make_graph<graph_t>(type, num_vertices, density, seed);

        vertex start;
        vertex end;
        if (type != "random")
        {
            start = premade_graphs::start_vertex(type);
            end = premade_graphs::end_vertex(type);
        }
        else
        {
            start = {0};
            end = {num_vertices - 1};
        }
        testShortestPath(g, start, end, type);
    }

    cout << "Tested " << test << " using graph " << type << endl;
    return 0;
}
