/**
 * @file maze.h
 * Declaration of the maze class.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_MAZE_H_
#define CS225_MAZE_H_

#include <cstdint>
#include <vector>

#include "epng.h"
#include "features/edge_weights.h"
#include "features/edge_labels.h"
#include "features/vertex_labels.h"
#include "graph.h"
#include "tools.h"

namespace cs225
{

/**
 * Represents a direction.
 */
enum class direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

/**
 * Prints a direction to a stream.
 * @param os the stream to print to
 * @param dir the direction to print
 * @return a reference to the os parameter
 */
std::ostream& operator<<(std::ostream& os, direction dir);

/**
 * This class represents a randomly generated square maze, and has
 * functions for finding its solution.
 *
 * Note that by "square" we are referring only to the cells of the maze:
 * the maze itself may have any dimensions (but is always rectangular).
 */
class maze
{
  public:
    /**
     * Creates a maze with the given width and height.
     *
     * You will start with a square grid (like graph paper) with the
     * specified height and width. You will select random walls to delete
     * without creating a cycle, until there are no more walls that can
     * be removed. **Do not remove walls on the grid's perimeter.**
     *
     * Hint: You should use an instance of a graph object from mp_graph.2
     * and apply one of your graph algorithms to it to generate the maze.
     * Remember: the resulting maze is a tree of corridors.
     *
     * @param width The width of the maze in terms of number of cells
     * @param height The height of the maze in terms of number of cells
     */
    maze(uint64_t width, uint64_t height);

    /**
     * This uses your representation of the maze to determine whether it is
     * possible to travel in the given direction from the square at
     * coordinates (x,y).
     *
     * For example, after maze m{2,2}, the possible input coordinates will
     * be (0,0), (0,1), (1,0), and (1,1).
     *
     * - direction::RIGHT represents a rightward step (+1 to the x coordinate)
     * - direction::DOWN represents a downward step (+1 to the y coordinate)
     * - direction::LEFT represents a leftward step (-1 to the x coordinate)
     * - direction::UP  represents an upward step (-1 to the y coordinate)
     *
     * You can not step off of the maze or through a wall.
     *
     * This function will be used by the grading program to verify that
     * your maze is a tree that occupies the whole grid, and to verify your
     * maze solution. So make sure that this function works!
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir The desired direction to move from the current cell
     * @return whether you can travel in the specified direction
     */
    bool can_travel(uint64_t x, uint64_t y, direction dir) const;

    /**
     * Sets whether or not the specified wall exists.
     *
     * This function should be fast (constant time). You can assume that in
     * grading we will not make your maze a non-tree and then call one of
     * the other member functions. set_wall should not prevent cycles from
     * occurring, but should simply set a wall to be present or not
     * present.  Our tests will call set_wall to copy a specific maze into
     * your implementation.
     *
     * **DO NOT THROW ANY EXCEPTIONS FROM THIS FUNCTION!**
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir Either right or down
     * @param exists true if setting the wall to exist, false otherwise
     */
    void set_wall(uint64_t x, uint64_t y, direction dir, bool exists);

    /**
     * Solves this maze.
     *
     * For each square on the bottom row (maximum y coordinate), there is a
     * distance from the origin (i.e. the top-left cell), which is defined as
     * the length (measured as a number of steps) of the only path through
     * the maze from the origin to that square.
     *
     * Select the square in the bottom row with the largest distance from the
     * origin as the destination of the maze. solve() returns the winning
     * path from the origin to the destination as a vector of directions.
     *
     * If multiple paths of maximum length exist, use the one with the
     * destination cell that has the smallest x value.
     *
     * Hint: this function should run in time linear in the number of cells
     * in the maze.
     *
     * @return a vector of directions taken to solve the maze
     */
    std::vector<direction> solve();

    /**
     * Draws the maze without the solution.
     *
     * First, create a new png. Set the dimensions of the png to
     * (width*10+1,height*10+1). where height and width were the arguments to
     * the constructor. Blacken the entire topmost row and leftmost column
     * of pixels, except the entrance (1,0) through (9,0).  For each square
     * in the maze, call its maze coordinates (x,y). If the right wall
     * exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k)
     * for k from 0 to 10. If the bottom wall exists, then blacken the
     * pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
     *
     * The resulting png will look like the sample image, except there will
     * be no exit from the maze and the red line will be missing.
     *
     * @return a png of the unsolved maze
     */
    epng::png draw() const;

    /**
     * This function calls draw, then solve; it modifies the png from draw
     * to show the solution vector and the exit.
     *
     * Start at pixel (5,5). Each direction in the solution vector
     * corresponds to a trail of 11 red pixels in the given direction. If the
     * first step is downward, color pixels (5,5) through (5,15) red. (Red is
     * 255,0,0 in RGB). Then if the second step is right, color pixels (5,15)
     * through (15,15) red. Then if the third step is up, color pixels
     * (15,15) through (15,5) red. Continue in this manner until you get to
     * the end of the solution vector, so that your output looks analogous
     * the above picture.
     *
     * Make the exit by undoing the bottom wall of the destination square:
     * call the destination maze coordinates (x,y), and whiten the pixels
     * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
     *
     * @return a png of the solved maze
     */
    epng::png draw_with_solution();

  private:
    /**
     * The width of the maze.
     */
    uint64_t width_;

    /**
     * The height of the maze.
     */
    uint64_t height_;

    /**
     * Our recommended storage for the maze. This is *not* the *only* way
     * to do it, it's just a particularly nice way.
     *
     * As a hint: remember that the vertex ids in the graph are integers 0
     * through \f$n\f$ where \f$n\f$ is the number of times you have called
     * `add_vertex()`.
     */
    graph<edge_weights<uint64_t>, edge_labels<tools::edge_state>> graph_;
    std::unordered_map<vertex, std::pair<uint64_t,uint64_t>> vtx_coords_reverse;
    std::vector<vertex> vtx_coords;

    bool coord_valid(uint64_t x1,int64_t x2change,uint64_t y1,int64_t y2change) const;
};
}
#endif
