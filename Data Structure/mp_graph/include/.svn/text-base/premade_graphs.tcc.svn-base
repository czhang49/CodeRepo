/**
 * @file premade_graphs.cpp
 *
 * This file contains the implementation of the premade graphs.
 * Updated by Sean Massung for Spring 2012
 *
 * @author Sean Massung
 * @date Spring 2011
 */

#include <type_traits>
#include <iostream>
#include "premade_graphs.h"

namespace cs225
{
namespace premade_graphs
{

namespace
{

template <class Graph>
typename std::enable_if<std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_us_weights(Graph& g, vertex vertices[])
{
    g.edge_weight(vertices[4], vertices[2], 315);
    g.edge_weight(vertices[4], vertices[1], 347);
    g.edge_weight(vertices[2], vertices[1], 126);
    g.edge_weight(vertices[6], vertices[0], 190);
    g.edge_weight(vertices[2], vertices[3], 406);
    g.edge_weight(vertices[3], vertices[6], 257);
    g.edge_weight(vertices[1], vertices[3], 210);
    g.edge_weight(vertices[3], vertices[0], 405);
    g.edge_weight(vertices[3], vertices[5], 235);
    g.edge_weight(vertices[5], vertices[0], 570);
    g.edge_weight(vertices[4], vertices[7], 353);
    g.edge_weight(vertices[1], vertices[7], 148);
    g.edge_weight(vertices[3], vertices[7], 310);
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_us_weights(Graph&, vertex[])
{
    // only add for weighted graphs
    return;
}

template <class Graph>
typename std::enable_if<std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_europe_weights(Graph& g, vertex vertices[])
{
    std::cout << "europe weights" << std::endl;
    g.edge_weight(vertices[4], vertices[3], 785);
    g.edge_weight(vertices[4], vertices[0], 314);
    g.edge_weight(vertices[0], vertices[3], 707);
    g.edge_weight(vertices[0], vertices[5], 451);
    g.edge_weight(vertices[0], vertices[6], 515);
    g.edge_weight(vertices[3], vertices[6], 213);
    g.edge_weight(vertices[6], vertices[5], 398);
    g.edge_weight(vertices[3], vertices[8], 892);
    g.edge_weight(vertices[3], vertices[1], 580);
    g.edge_weight(vertices[6], vertices[1], 546);
    g.edge_weight(vertices[5], vertices[1], 524);
    g.edge_weight(vertices[5], vertices[7], 398);
    g.edge_weight(vertices[8], vertices[1], 504);
    g.edge_weight(vertices[1], vertices[7], 174);
    g.edge_weight(vertices[1], vertices[9], 321);
    g.edge_weight(vertices[8], vertices[2], 246);
    g.edge_weight(vertices[1], vertices[2], 687);
    g.edge_weight(vertices[2], vertices[9], 570);
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_europe_weights(Graph&, vertex[])
{
    std::cout << "skip europe weights" << std::endl;
    // only add for weighted graphs
    return;
}

template <class Graph>
typename std::enable_if<std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_japan_weights(Graph& g, vertex vertices[])
{
    g.edge_weight(vertices[4], vertices[3], 124);
    g.edge_weight(vertices[3], vertices[5], 85);
    g.edge_weight(vertices[5], vertices[8], 24);
    g.edge_weight(vertices[3], vertices[1], 26);
    g.edge_weight(vertices[5], vertices[1], 62);
    g.edge_weight(vertices[5], vertices[6], 21);
    g.edge_weight(vertices[1], vertices[6], 73);
    g.edge_weight(vertices[6], vertices[8], 15);
    g.edge_weight(vertices[6], vertices[0], 60);
    g.edge_weight(vertices[8], vertices[0], 63);
    g.edge_weight(vertices[7], vertices[2], 27);
    g.edge_weight(vertices[2], vertices[4], 65);
    g.edge_weight(vertices[2], vertices[8], 226);
    g.edge_weight(vertices[4], vertices[8], 160);
    g.edge_weight(vertices[4], vertices[5], 140);
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_weights<int>, Graph>::value>::type
    add_japan_weights(Graph&, vertex[])
{
    // only add for weighted graphs
    return;
}
}

inline vertex start_vertex(std::string mapType)
{
    if (mapType == "us")
        return vertex{4};
    if (mapType == "europe")
        return vertex{3};
    return vertex{4};
}

inline vertex end_vertex(std::string mapType)
{
    if (mapType == "us")
        return vertex{0};
    if (mapType == "europe")
        return vertex{7};
    return vertex{0};
}

template <class Graph>
Graph create_us_map()
{
    Graph g;
    size_t numCities = 8;

    std::string labels[] = {"WashingtonDC", "Champaign",  "Chicago",
                            "Cincinnati",   "KansasCity", "Nashville",
                            "Pittsburgh",   "StLouis"};

    vertex vertices[numCities];
    for (size_t i = 0; i < numCities; ++i)
    {
        vertices[i] = g.add_vertex();
        g.vertex_label(vertices[i], labels[i]);
    }

    g.add_edge(vertices[4], vertices[2]);
    g.add_edge(vertices[4], vertices[1]);
    g.add_edge(vertices[2], vertices[1]);
    g.add_edge(vertices[6], vertices[0]);
    g.add_edge(vertices[2], vertices[3]);
    g.add_edge(vertices[3], vertices[6]);
    g.add_edge(vertices[1], vertices[3]);
    g.add_edge(vertices[3], vertices[0]);
    g.add_edge(vertices[3], vertices[5]);
    g.add_edge(vertices[5], vertices[0]);
    g.add_edge(vertices[4], vertices[7]);
    g.add_edge(vertices[1], vertices[7]);
    g.add_edge(vertices[3], vertices[7]);

    add_us_weights(g, vertices);

    return g;
}

template <class Graph>
Graph create_europe_map()
{
    Graph g;
    size_t numCities = 10;

    std::string labels[] = {"Barcelona", "Berlin", "Helsinki", "London",
                            "Madrid",    "Milan",  "Paris",    "Prague",
                            "Stockholm", "Warsaw"};

    vertex vertices[numCities];
    for (size_t i = 0; i < numCities; ++i)
    {
        vertices[i] = g.add_vertex();
        g.vertex_label(vertices[i], labels[i]);
    }

    g.add_edge(vertices[4], vertices[3]);
    g.add_edge(vertices[4], vertices[0]);
    g.add_edge(vertices[0], vertices[3]);
    g.add_edge(vertices[0], vertices[5]);
    g.add_edge(vertices[0], vertices[6]);
    g.add_edge(vertices[3], vertices[6]);
    g.add_edge(vertices[6], vertices[5]);
    g.add_edge(vertices[3], vertices[8]);
    g.add_edge(vertices[3], vertices[1]);
    g.add_edge(vertices[6], vertices[1]);
    g.add_edge(vertices[5], vertices[1]);
    g.add_edge(vertices[5], vertices[7]);
    g.add_edge(vertices[8], vertices[1]);
    g.add_edge(vertices[1], vertices[7]);
    g.add_edge(vertices[1], vertices[9]);
    g.add_edge(vertices[8], vertices[2]);
    g.add_edge(vertices[1], vertices[2]);
    g.add_edge(vertices[2], vertices[9]);

    add_europe_weights(g, vertices);

    return g;
}

template <class Graph>
Graph create_japan_map()
{
    Graph g;
    size_t numCities = 9;

    std::string labels[] = {"Hitachinaka", "Komoro", "Kyoto",
                            "Nagano",      "Nagoya", "Ome",
                            "Omiya",       "Osaka",  "Tokyo"};

    vertex vertices[numCities];
    for (size_t i = 0; i < numCities; ++i)
    {
        vertices[i] = g.add_vertex();
        g.vertex_label(vertices[i], labels[i]);
    }

    g.add_edge(vertices[4], vertices[3]);
    g.add_edge(vertices[3], vertices[5]);
    g.add_edge(vertices[5], vertices[8]);
    g.add_edge(vertices[3], vertices[1]);
    g.add_edge(vertices[5], vertices[1]);
    g.add_edge(vertices[5], vertices[6]);
    g.add_edge(vertices[1], vertices[6]);
    g.add_edge(vertices[6], vertices[8]);
    g.add_edge(vertices[6], vertices[0]);
    g.add_edge(vertices[8], vertices[0]);
    g.add_edge(vertices[7], vertices[2]);
    g.add_edge(vertices[2], vertices[4]);
    g.add_edge(vertices[2], vertices[8]);
    g.add_edge(vertices[4], vertices[8]);
    g.add_edge(vertices[4], vertices[5]);

    add_japan_weights(g, vertices);

    return g;
}
}
}
