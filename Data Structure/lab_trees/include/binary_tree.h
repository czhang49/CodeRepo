/**
 * @file binary_tree.h
 * Declaraction of the binary_tree class. You will probably need to modify this
 *  file to add helper functions.
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "random.h"

/**
 * The binary_tree class represents a templated linked-memory tree data
 * structure.
 */
template <typename T>
class binary_tree
{
  private:
    /**
     * Represents a tree node; that is, an element in a binary_tree.
     * It has a data element and pointers to its left and right children.
     */
    struct node
    {
        /// The data stored in this node
        T elem;
        /// The left subtree
        std::unique_ptr<node> left;
        /// The right subtree
        std::unique_ptr<node> right;

        /**
         * node element constructor; sets children to point to nullptr.
         * @param element The templated data element that the constructed
         *  node will hold.
         */
        node(T element) : elem{std::move(element)}
        {
            // nothing; left and right are nullptr because of default
            // unique_ptr constructor
        }
    };

  public:
    /**
     * Constructor to create an empty tree.
     *
     * The default constructor for a unique_ptr sets it to null, so we can
     * use the system-provided default constructor here.
     */
    binary_tree() = default;

    /**
     * Copy constructor.
     * We must manually specify this because unique_ptr is not copyable.
     */
    binary_tree(const binary_tree& other);

    /**
     * Move constructor.
     * The system-provided default move constructor move-constructs each of
     * the member variables of the class, which is exactly what we want for
     * binary_tree.
     */
    binary_tree(binary_tree&& other) = default;

    /**
     * Destructor; frees all nodes associated by this tree.
     * Since the unique_ptr destructor for head will delete the root of the
     * tree, and the unique_ptr destructors within the nodes will traverse
     * and delete the remaining node, we can safely use the system-provided
     * default destructor here.
     */
    ~binary_tree() = default;

    /**
     * Assignment operator.
     * @param rhs The tree to make a copy of
     * @return A reference to the current tree
     */
    binary_tree& operator=(binary_tree rhs);

    /**
     * Frees all nodes associated with this tree and sets it to be empty.
     */
    void clear();

    /**
     * Swaps with another binary_tree.
     *
     * @param other The tree to swap with
     */
    void swap(binary_tree& other);

    /**
     * Inserts into the binary_tree.
     * @param elem The element to insert
     * @param sorted By default, this parameter is false. That means that
     * the element takes a pseudo-random path to a leaf where it is
     * inserted. If true, the insert function will act like it does in a
     * BST.
     */
    void insert(T elem, bool sorted = false);

    /**
     * Prints the contents of the tree to stdout.
     */
    void print() const;

    /**
     * This lab deals with the following six helper functions:
     */

    /**
     * @return The height of the binary tree. Recall that the height of a
     * binary tree is just the length of the longest path from the root to
     * a leaf, and that the height of an empty tree is -1.
     */
    int height() const;

    /**
     * Prints out the values of the nodes of a binary tree in order. That
     * is, everything to the left of a node will be printed out before that
     * node itself, and everything to the right of a node will be printed
     * out after that node.
     */
    void printLeftToRight() const;

    /**
     * Flips the tree over a vertical axis, modifying the tree itself (not
     * creating a flipped copy).
     */
    void mirror();

    /**
     * @return True if an in-order traversal of the tree would produce a
     * nondecreasing list output values, and false otherwise. This is also
     * the criterion for a binary tree to be a binary search tree.
     */
    bool isOrdered() const;

    /**
     * Prints out all the possible paths from the root of the tree to any
     * leaf node.  That is, all sequences starting at the root node and
     * continuing downwards, ending at a leaf node. Paths ending in a left
     * node should be printed before paths ending in a node further to the
     * right.
     */
    void printPaths() const;

    /**
     * Each node in a tree has a distance from the root node - the depth of
     * that node, or the number of edges along the path from that node to
     * the root. This function returns the sum of the distances of all
     * nodes to the root node (the sum of the depths of all the nodes).
     * Your solution should take O(n) time, where n is the number of nodes
     * in the tree.
     * @return The sum of the distances of all nodes to the root
     */
    uint64_t sumDistances() const;

  private:
    /// The root of our tree
    std::unique_ptr<node> root_;
	void mirror(node* subroot);
    void printPaths(std::vector<uint64_t> prev,node* subroot) const;
	uint64_t sumDistances(uint64_t prev,node* subroot) const;
	bool isOrdered(node* subroot) const;
	bool leftisallsmall(node* start, T elem) const;
	bool rightisalllarge(node* start,T elem) const;
	/**
     * Private helper function for the public height function.
     * @param subRoot The current node in the recursion
     * @return The height of the subtree
     */
    int height(const node* subRoot) const;

    /**
     * Private helper function for the public printLeftToRight function.
     * @param subRoot The current node in the recursion
     */
    void printLeftToRight(const node* subRoot) const;

    /**
     * Private helper function for the public insert function.
     * @param node The current node in the recursion
     * @param elem The element to insert
     * @param sorted By default, this parameter is false. That means that
     * the element takes a pseudo-random path to a leaf where it is
     * inserted. If true, the insert function will act like it does in a
     * BST.
     */
    void insert(std::unique_ptr<node>& node, T elem, bool sorted);

    /**
     * Helper function for cctor.
     * @param subRoot The current node in the recursion
     */
    std::unique_ptr<node> copy(const node* subRoot);
};

#include "binary_tree_given.tcc"
#include "binary_tree.tcc"
#endif
