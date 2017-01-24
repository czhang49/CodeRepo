/**
 * @file tools.tcc
 * Definition of utility functions on graphs.
 */

#include <limits>
#include <queue>

#include "dsets.h"
#include "tools.h"

namespace cs225
{
namespace tools
{

template <class Graph>
typename Graph::edge_weight_type min_weight_edge(Graph& g)
{
    	using weight_t = typename Graph::edge_weight_type;
    	weight_t min = std::numeric_limits<weight_t>::max();
    	edge min_edge{g.start_vertex(), g.start_vertex()};

    	vertex_map<vertex_state> vtx_mark;
    	for (const auto& v : g.vertices())
        	vtx_mark[v] = vertex_state::UNEXPLORED;

	
	edge_map <edge_state> edg_mark;
	for (const auto& e:g.edges()){
		edg_mark[e] = edge_state::UNEXPLORED;
	}

	
    	/// @todo your code here
	std::queue<vertex> vertex_tolook;
	vertex curr = g.start_vertex();
	vertex_tolook.push(curr);
	vtx_mark[curr] = vertex_state::VISITED;
	
	while (!vertex_tolook.empty()){
		curr = vertex_tolook.front();
		vertex_tolook.pop();

		for ( const auto& v: g.adjacent(curr) ){

			if (edg_mark[{curr,v}] == edge_state::UNEXPLORED){
				if (g.edge_weight(curr,v) < min){				
					min = g.edge_weight(curr,v);
					min_edge = {curr,v};
				}
			}
			if (vtx_mark[v] == vertex_state::UNEXPLORED){
				vertex_tolook.push(v);
				vtx_mark[v] = vertex_state::VISITED;
				edg_mark[{curr,v}] = edge_state::DISCOVERY;
				edg_mark[{v,curr}] = edge_state::DISCOVERY;
			}else if (edg_mark[{curr,v}] == edge_state::UNEXPLORED){
				edg_mark[{curr,v}] = edge_state::BACK;
				edg_mark[{v,curr}] = edge_state::BACK;
			}
			
		}
		
	}
	
	edg_mark[min_edge] = edge_state::MIN;  
	edg_mark[min_edge.reverse()] = edge_state::MIN;  

	for ( const auto& e: g.edges()){
		g.edge_label(e,edg_mark[e]);
	}

	return min;
	
}

template <class Graph>
uint64_t shortest_path_length(Graph& g, vertex start, vertex end)
{
    	/// @todo your code here
	std::queue<vertex> vtx_queue;
	vertex_map <vertex_state> vtx_map;
	edge_map <edge_state> edge_map;
	
	for (const auto & v : g.vertices()){
		vtx_map[v] = vertex_state::UNEXPLORED;
	}
	for (const auto & e : g.edges()){
		edge_map[e] = edge_state::UNEXPLORED;
	}

	vtx_map[start] = vertex_state::VISITED;
	vtx_queue.push(start);

	vertex hintvertex;
	bool found = 0;
	uint64_t distance=1;

	std::hash<cs225::vertex> hash1;
	std::hash<cs225::vertex> hash2;

	while(!vtx_queue.empty()){
				
		vertex curr = vtx_queue.front();
		vtx_queue.pop();
		
		for (const auto & v: g.adjacent(curr)){
			if ( hash1(v) == hash2(end)){
				g.edge_label({curr,v},edge_state::MINPATH);
				g.edge_label({v,curr},edge_state::MINPATH);
				hintvertex = curr;
				found = 1;
				break;
			}
			
			if (vtx_map[v] == vertex_state::UNEXPLORED){
				vtx_queue.push(v);
				vtx_map[v] = vertex_state::VISITED;
				edge_map[{curr,v}] = edge_state::DISCOVERY;
				
			} /*else if (edge_map[{curr,v}] == edge_state::UNEXPLORED){
				edge_map[{curr,v}] = edge_state::BACK;
				edge_map[{v,curr}] = edge_state::BACK;
			}*/
		}
		
		if (found)
			break;	
	}

	
	// there is only one way/path to arrive at a vertex (the vertex being the destination), so we can backtrace the path to where we come from using this property.
	// fyi, there is multiple way/path to leave a vertex (the vertex being the source).
	bool finished = 0;
	while(1){
		for ( const auto v : g.adjacent(hintvertex) ){
			if (hash1(hintvertex) == hash2(start)){
				finished =1;
				break;
			}
			if (edge_map[{v,hintvertex}] == edge_state::DISCOVERY){
				g.edge_label ({v,hintvertex},edge_state::MINPATH);
				g.edge_label ({hintvertex,v},edge_state::MINPATH);
				hintvertex = v;
				distance++;
				break;
			}
		}

		if (finished) 
			break;

	}

	return distance;

}

template <class Graph>
void mark_mst(Graph& g)
{
    for (const auto& e : minimum_spanning_tree(g))
        g.edge_label(e, edge_state::MST);
}

template <class Graph>
edge_set minimum_spanning_tree(const Graph& g)
{
    	// sort all the edges
    	auto edges = g.edges();
	edge_set edgeset;

    	std::vector<edge> pq{edges.begin(), edges.end()};

	// sort using a lambda expression and capturing the parameter g. the std::sort assumes this type of function and return method
	// by using the passed in iterator, the vector<edge> itself is sorted
    	std::sort(pq.begin(), pq.end(), [&](edge e1, edge e2)
    	{ return g.edge_weight(e1) < g.edge_weight(e2); });

    	/// @todo your code here
	// the vertex_map stores the element number, not the index number
	vertex_map<int> vtx_map;
	int index = 0;
	for (const auto & v: g.vertices()){
		index++;
		vtx_map[v] = index;
	}

	// minimum spanning tree use dsets
	dsets vtx_dset;
	vtx_dset.add_elements(index);

	for (auto it = pq.begin(); it!=pq.end(); it++){
		if (vtx_dset.find(vtx_map[(*it).source]) != vtx_dset.find(vtx_map[(*it).dest]) ){
			edgeset.insert((*it));
			edgeset.insert((*it).reverse());
			vtx_dset.merge(vtx_map[(*it).source],vtx_map[(*it).dest]);
		}
	}
	
	return edgeset;
}
}
}
