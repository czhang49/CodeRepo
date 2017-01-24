/**
 * @file quadtree_given.h
 * Contains functions of the quadtree class used for grading.
 */

  public:

    /**
     * Given: prints the leaves of the quadtree using a preorder traversal.
     */
    void print(std::ostream& out = std::cout) const;

    /**
     * Given: compares the current quadtree with the parameter quadtree, and
     *  determines whether or not the two are the same.
     *
     * @param other Reference to a const quadtree object, against which the
     *  current quadtree will be compared
     * @return True if the quadtrees are deemed "equal", and false otherwise
     * @note This method relies on the private helper method equal()
     */
    bool operator==(const quadtree & other) const;

  private:

    /**
     * Given: prints the contents of the quadtree using a preorder traversal.
     *
     * @param current Pointer to the root of the subquadtree which we wish
     *   to print
     * @param level Current recursion depth; used for determining when to
     *  terminate recursion (see note below)
     */
    void print(std::ostream& out, const node* current, int level) const;

    /**
     * Given: compares the subquadtree rooted at firstPtr with the subquadtree
     *  rooted at secondPtr, and determines whether the two are the same.
     *
     * @param firstPtr Pointer to the root of a subtree of the "first"
     *  quadtree under consideration
     * @param secondPtr Pointer to the root of a subtree of the "second"
     *  quadtree under consideration
     * @return True if the subquadtrees are deemed "equal", and false
     *  otherwise
     */
    bool equal(const node* firstPtr, const node* secondPtr) const;
