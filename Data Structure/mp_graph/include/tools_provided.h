/**
 * @file tools_provided.h
 * Declarations of provided helper functions on graphs.
 *
 * @author Chase Geigle
 * @date Summer 2014
 *
 * Ported from the old graph library by Sean Massung, Spring 2011
 */

#ifndef CS225_TOOLS_PROVIDED_H_
#define CS225_TOOLS_PROVIDED_H_

#include <cstdint>
#include <string>

namespace cs225
{
namespace tools
{

/**
 * Saves a graph as a png image, using Graphviz's "neato" application. For
 * this to work, you will need to have your system's Graphviz package
 * installed.
 *
 * @param graph The graph to save
 * @param title The filename for the desired png image
 */
template <class Graph>
void save_png(const Graph& graph, const std::string& title);

/**
 * Prints a graph to standard out.
 */
template <class Graph>
void print(const Graph& graph);

/**
 * Takes snapshots of graphs.
 */
class snapshot
{
  public:
    snapshot(std::string filename)
        : pic_num_{0}, filename_{std::move(filename)}
    {
        // nothing
    }

    template <class Graph>
    void operator()(Graph& g);

  private:
    uint64_t pic_num_;
    std::string filename_;
};
}
}

#include "tools_provided.tcc"

#endif
