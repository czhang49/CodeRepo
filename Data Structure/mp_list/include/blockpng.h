/**
 * @file blockpng.h
 * @author Chase Geigle
 * @date Fall 2011
 * @date (Modified) Summer 2014
 */
#ifndef BLOCKPNG_H_
#define BLOCKPNG_H_
#include "epng.h"

#include <vector>

/**
 * A visualization for mp_list.
 */
namespace blockpng
{
/**
 * Generates a new png given a source, a vector of block ids, and a block
 * size (d).
 *
 * @param src The image to base off of
 * @param vect A vector of block ids
 * @param d The block size
 * @return a png consisting of the blocks laid out in the order specified
 * by the vector
 */
epng::png generate(const epng::png& src, const std::vector<int>& vect, int d);
}
#endif
