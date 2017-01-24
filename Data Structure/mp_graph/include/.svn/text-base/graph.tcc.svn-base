/**
 * @file graph.tcc
 * Definition of the graph class.
 *
 * Written for CS 225 Spring 2011.
 *
 * @author Sean Massung
 * @author Abigail Steitz
 * @author Chase Geigle
 */

#include <algorithm>
#include <random>

#include "graph.h"

namespace cs225
{

namespace
{
/**
 * Base case for the remove_vertex_callbacks chain.
 */
inline void remove_vertex_callbacks(vertex)
{
    return;
}

/**
 * Invoked when a vertex is removed from the graph to ensure that all
 * features also update themselves to reflect the removal.
 */
template <class Feat, class... Feats>
void remove_vertex_callbacks(vertex v, Feat& feat, Feats&... feats)
{
    feat.remove_vertex(v);
    remove_vertex_callbacks(v, feats...);
}

/**
 * Base case for the remove_edge_callbacks chain.
 */
inline void remove_edge_callbacks(edge)
{
    return;
}

/**
 * Invoked when an edge is removed from teh graph to ensure that all
 * features also update themselves to reflect the removeal.
 */
template <class Feat, class... Feats>
void remove_edge_callbacks(edge e, Feat& feat, Feats&... feats)
{
    feat.remove_edge(e);
    remove_edge_callbacks(e, feats...);
}
}

template <class... GraphFeatures>
graph<GraphFeatures...>::graph(uint64_t num_vertices, uint8_t density,
                               uint64_t seed)
{
    if (num_vertices < 2)
        throw exception{"num_vertices too low"};
    if (density > 100)
        throw exception{"density above 100"};

    std::vector<vertex> vertices(num_vertices);
    std::generate(std::begin(vertices), std::end(vertices), [&]()
    { return add_vertex(); });

    // make sure all vertices are connected
    std::mt19937_64 rng{seed};
    std::shuffle(std::begin(vertices), std::end(vertices), rng);
    for (uint64_t i = 0; i < vertices.size() - 1; ++i)
    {
        const auto& curr = vertices[i];
        const auto& next = vertices[i + 1];
        add_edge(curr, next);
    }

    auto num_edges = vertices.size() - 1;

    // Add as many edges to the graph until it is dense enough.
    // Edges are added by comparing each possible pair of vertices and
    // adding when the random_number falls below density

    // stopping criterion: do we have enough edges? This is checked inside
    // both for loops
    auto stop = [&]()
    { return 100 * num_edges / (num_vertices * num_vertices) > density; };

    // random number generation between 0 and 100
    std::uniform_int_distribution<uint8_t> dist{0, 100};
    for (uint64_t i = 0; i < vertices.size() && !stop(); ++i)
    {
        for (uint64_t j = 0; j < vertices.size() && !stop(); ++j)
        {
            // don't add self loops
            if (i == j)
                continue;

            const auto& source = vertices[i];
            const auto& dest = vertices[j];

            // if we already have this edge, don't attempt to add it
            if (has_edge(source, dest))
                continue;

            auto random_number = dist(rng);
            if (random_number <= density)
            {
                add_edge(source, dest);
                ++num_edges;
            }
        }
    }
}

template <class... GraphFeatures>
vertex graph<GraphFeatures...>::start_vertex() const
{
    return adjacency_sets_.begin()->first;
}

template <class... GraphFeatures>
vertex_set graph<GraphFeatures...>::vertices() const
{
    std::unordered_set<vertex> ret;
    for (const auto& p : adjacency_sets_)
        ret.insert(p.first);
    return ret;
}

template <class... GraphFeatures>
edge_set graph<GraphFeatures...>::edges() const
{
    edge_set edges;
    for (const auto& p : adjacency_sets_)
    {
        const auto& u = p.first;
        for (const auto& v : adjacent(u))
        {
            edge e{u, v};
            if (edges.find(e) != edges.end())
                continue;
            if (edges.find(e.reverse()) != edges.end())
                continue;
            edges.emplace(e);
        }
    }
    return edges;
}

template <class... GraphFeatures>
const vertex_set& graph<GraphFeatures...>::adjacent(vertex v) const
{
    assert_exists(v);
    return adjacency_sets_.at(v);
}

template <class... GraphFeatures>
vertex graph<GraphFeatures...>::add_vertex()
{
    auto vtx = next_vertex_;
    ++next_vertex_;
    adjacency_sets_.emplace(vtx, vertex_set{});
    return vtx;
}

template <class... GraphFeatures>
void graph<GraphFeatures...>::remove_vertex(vertex v)
{
    assert_exists(v);

    // need to make a copy here since we are modifying the set in this loop
    auto adj = adjacent(v);
    for (const auto& u : adj)
    {
        remove_edge(u, v);
    }

    adjacency_sets_.erase(v);

    remove_vertex_callbacks(v, static_cast<GraphFeatures&>(*this)...);
}

template <class... GraphFeatures>
edge graph<GraphFeatures...>::add_edge(vertex u, vertex v)
{
    assert_exists(u);
    assert_exists(v);

    adjacency_sets_[u].insert(v);
    adjacency_sets_[v].insert(u);

    return {u, v};
}

template <class... GraphFeatures>
void graph<GraphFeatures...>::remove_edge(vertex u, vertex v)
{
    assert_exists(u);
    assert_exists(v);
    assert_exists(u, v);

    adjacency_sets_[u].erase(v);
    adjacency_sets_[v].erase(u);

    remove_edge_callbacks({u, v}, static_cast<GraphFeatures&>(*this)...);
}

template <class... GraphFeatures>
void graph<GraphFeatures...>::remove_edge(edge e)
{
    remove_edge(e.source, e.dest);
}

template <class... GraphFeatures>
bool graph<GraphFeatures...>::has_edge(vertex u, vertex v) const
{
    assert_exists(u);
    assert_exists(v);
    const auto& adj = adjacent(u);
    return adj.find(v) != adj.end();
}

template <class... GraphFeatures>
void graph<GraphFeatures...>::assert_exists(vertex v) const
{
    if (adjacency_sets_.find(v) == adjacency_sets_.end())
        throw exception{"nonexistent vertex"};
}

template <class... GraphFeatures>
void graph<GraphFeatures...>::assert_exists(vertex u, vertex v) const
{
    if (!has_edge(u, v))
        throw exception{"nonexistent edge"};
}
}
