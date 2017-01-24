/**
 * @file quadtree.h
 * quadtree class definition.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include "epng.h"

namespace cs225
{

/**
 * A tree structure that is used to compress epng::png images.
 */
class quadtree
{
  public:

    // Constructors
    quadtree();
    quadtree(const epng::png &source, uint64_t resolution);
    quadtree(const quadtree &other);
    quadtree(quadtree && other);

    // Destructor;
    ~quadtree()=default;

    // Some must-have utility functions
    quadtree& operator= (quadtree other);
    void swap (quadtree &other);
    void build_tree(const epng::png & source, uint64_t resolution);
    const epng::rgba_pixel& operator()(uint64_t x, uint64_t y) const;
    epng::png decompress() const;
    void rotate_clockwise();
    //void prune(uint32_t tolerance);
    //uint64_t pruned_size(uint32_t tolerance) const;
    //uint32_t ideal_prune(uint64_t num_leaves) const;

    
  private:
    /**
     * A simple class representing a single node of a quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class node
    {
      public:
	node();
	node(const node&);

        std::unique_ptr<node> northwest;
        std::unique_ptr<node> northeast;
        std::unique_ptr<node> southwest;
        std::unique_ptr<node> southeast;

        epng::rgba_pixel element; // the pixel stored as this node's "data"
    };

    std::unique_ptr<node> root_; // the root of the tree
    uint64_t resol;

    void colorfy_element(epng::rgba_pixel& element, const epng::png& source, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy); // colorfy the given element with the source and range 
    void create_child(std::unique_ptr<node>& target_ptr, const std::unique_ptr<node>& given_ptr); // create a child node from a given node, this is for copy
    void create_child(std::unique_ptr<node>& target_ptr,const epng::png& source, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy); // create a node and colorfy it with the given range
    const epng::rgba_pixel& find_rgba_pixel(uint64_t x,uint64_t y,uint64_t left_upX,uint64_t left_upY, uint64_t curr_range, const std::unique_ptr<node>& ptr) const;
    void switch_pointer(std::unique_ptr<node>& ptr);
   public:
   std::unique_ptr<node>& get_root() ;
   const std::unique_ptr<node>& get_root_only() const;
   uint64_t get_resol() const;

/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};
}
#endif
