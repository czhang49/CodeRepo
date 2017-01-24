/**
 * @file tools_provided.tcc
 * Definitions of provided helper functions on graphs.
 *
 * @author Chase GEigle
 * @date Summer 2014
 *
 * Ported from the old graph library by Sean Massung, Spring 2011
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

#include "features/edge_labels.h"
#include "features/edge_weights.h"
#include "features/vertex_labels.h"
#include "graph.h"
#include "tools.h"
#include "tools_provided.h"

namespace cs225
{
namespace tools
{

namespace
{

template <class Graph>
typename std::enable_if<
    !std::is_base_of<vertex_labels<std::string>, Graph>::value,
    std::string>::type
    vertex_label(const Graph&, vertex)
{
    return "";
}

template <class Graph>
typename std::enable_if<
    std::is_base_of<vertex_labels<std::string>, Graph>::value,
    std::string>::type
    vertex_label(const Graph& graph, vertex u)
{
    try
    {
        return graph.vertex_label(u);
    }
    catch (...)
    {
        return "";
    }
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_labels<edge_state>, Graph>::value,
                        std::string>::type
    edge_label(const Graph&, vertex, vertex)
{
    return ""; // only for edge-labeled graphs
}

template <class Graph>
typename std::enable_if<std::is_base_of<edge_labels<edge_state>, Graph>::value,
                        std::string>::type
    edge_label(const Graph& graph, vertex u, vertex v)
{
    try
    {
        const auto& lbl = graph.edge_label(u, v);
        switch (lbl)
        {
            case edge_state::UNEXPLORED:
                return "UNEXPLORED";
            case edge_state::DISCOVERY:
                return "DISCOVERY";
            case edge_state::BACK:
                return "BACK";
            case edge_state::CROSS:
                return "CROSS";
            case edge_state::MIN:
                return "MIN";
            case edge_state::MINPATH:
                return "MINPATH";
            case edge_state::MST:
                return "MST";
            default:
                return "";
        }
    }
    catch (...)
    {
        return "";
    }
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_weights<int>, Graph>::value>::type
    handle_weight_neato(std::ofstream&, const Graph&, vertex, vertex)
{
    // only for weighted graphs
    return;
}

template <class Graph>
typename std::enable_if<std::is_base_of<edge_weights<int>, Graph>::value>::type
    handle_weight_neato(std::ofstream& neato_file, const Graph& graph, vertex u,
                        vertex v)
{
    neato_file << "[label=\"" << graph.edge_weight(u, v) << "\"]";
}

template <class Graph>
typename std::enable_if<!std::is_base_of<edge_weights<int>, Graph>::value>::type
    handle_weight_cout(const Graph&, vertex, vertex)
{
    // only for weighted graphs
    return;
}

template <class Graph>
typename std::enable_if<std::is_base_of<edge_weights<int>, Graph>::value>::type
    handle_weight_cout(const Graph& graph, vertex u, vertex v)
{
    std::cout << "weight = " << graph.edge_weight(u, v);
}
}

template <class Graph>
void save_png(const Graph& graph, const std::string& title)
{
    std::ofstream neato_file;
    std::string filename = "images/" + title + ".dot";
    neato_file.open(filename);

    if (!neato_file)
        throw typename Graph::exception{"couldn't create " + filename + ".dot"};

    neato_file
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"160\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"6.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"6.0\"];\n";

    for (const auto& u : graph.vertices())
    {
        auto u_label = vertex_label(graph, u);
        for (const auto& v : graph.adjacent(u))
        {
            auto v_label = vertex_label(graph, v);

            neato_file << "\t\"" << u;
            if (!u_label.empty())
                neato_file << " - " << u_label;
            neato_file << "\" -- \"" << v;
            if (!v_label.empty())
                neato_file << " - " << v_label;
            neato_file << "\"";

            auto label = edge_label(graph, u, v);

            if (label == "MST" || label == "MIN" || label == "MINPATH")
                neato_file << "[color=\"blue\"]";
            else if (label == "CROSS" || label == "BACK")
                neato_file << "[color=\"red\"]";
            else if (label == "DISCOVERY")
                neato_file << "[color=\"green\"]";

            handle_weight_neato(neato_file, graph, u, v);
            neato_file << ";\n";
        }
    }

    neato_file << "}";
    neato_file.close();
    auto command = "neato -Tpng " + filename + " -o " + "images/" + title +
                   ".png 2> /dev/null";
    // TODO: can we eliminate the system() here?
    system(command.c_str());
    auto rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}

template <class Graph>
void print(const Graph& graph)
{
    for (const auto& u : graph.vertices())
    {
        std::cout << u;
        auto lbl = vertex_label(graph, u);
        if (!lbl.empty())
            std::cout << " " << lbl;
        std::cout << std::endl;
        for (const auto& v : graph.adjacent(u))
        {
            std::stringstream ss;
            ss << v;
            auto vtx_col = "    => " + ss.str();
            vtx_col += " " + vertex_label(graph, v);
            std::cout << std::left << std::setw(26) << vtx_col;
            auto edge_col = "edge label = \"" + edge_label(graph, u, v) + "\"";
            std::cout << std::left << std::setw(26) << edge_col;
            handle_weight_cout(graph, u, v);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

template <class Graph>
void snapshot::operator()(Graph& g)
{
    save_png(g, filename_ + std::to_string(pic_num_));
    ++pic_num_;
}
}
}
