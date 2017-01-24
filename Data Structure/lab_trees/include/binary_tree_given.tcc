/**
 * @file binary_tree_given.tcc
 * Definitions of some standard binary tree functions.
 *
 * YOU WON'T NEED TO MODIFY THIS FILE.
 *
 * In fact, you shouldn't have to read below this line. To see what the
 * given functions do, read the header file.
 */

#include "printtree.h"

template <class T>
binary_tree<T>::binary_tree(const binary_tree& other)
    : root_{copy(other.root_.get())}
{
    /* nothing */
}

template <class T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree<T> rhs)
{
    swap(rhs);
    return *this;
}

template <class T>
void binary_tree<T>::clear()
{
    root_ = nullptr;
    // setting root_ to null here will release the resource associated with
    // the top node in the tree, which will cause a recursive release of
    // all of the nodes in the tree via the unique_ptr destructor.
}

template <class T>
void binary_tree<T>::swap(binary_tree& other)
{
    std::swap(root_, other.root_);
}

// This is a template so we can declare it outside of the .h file - we don't
// need to actually see
// the binary_tree<T>::node class
template <class Node>
class binary_treeNodeDescriptor
    : public GenericNodeDescriptor<binary_treeNodeDescriptor<Node>>
{
  public:
    binary_treeNodeDescriptor(const Node* Node_ptr) : n{Node_ptr}
    {
        // nothing
    }

    bool isNull() const
    {
        return !n;
    }

    std::string key() const
    {
        std::stringstream ss;
        ss << n->elem;
        return ss.str();
    }

    binary_treeNodeDescriptor left() const
    {
        return binary_treeNodeDescriptor(n->left.get());
    }

    binary_treeNodeDescriptor right() const
    {
        return binary_treeNodeDescriptor(n->right.get());
    }

  private:
    const Node* n;
};

template <class T>
void binary_tree<T>::print() const
{
    printTree(binary_treeNodeDescriptor<node>(root_.get()));
}

template <class T>
void binary_tree<T>::insert(T elem, bool sorted /* = false */)
{
    insert(root_, std::move(elem), sorted);
}

template <class T>
void binary_tree<T>::insert(std::unique_ptr<node>& subroot, T elem, bool sorted)
{
    // If we're at a nullptr pointer, we can put our element here
    if (!subroot)
    {
        subroot = std::make_unique<node>(std::move(elem));
    }
    // If sorted, go left/right based on ordering
    // If random, go left or right based on pseudorandom even/odd
    else if (sorted ? elem < subroot->elem : util::urand() % 2 == 0)
    {
        insert(subroot->left, std::move(elem), sorted);
    }
    else // right side / larger
    {
        insert(subroot->right, std::move(elem), sorted);
    }
}

template <class T>
auto binary_tree<T>::copy(const node* subRoot) -> std::unique_ptr<node>
{
    if (!subRoot)
        return {};

    // Copy this node and it's children
    auto newnode = std::make_unique<node>(subRoot->elem);
    newnode->left = copy(subRoot->left.get());
    newnode->right = copy(subRoot->right.get());
    return newnode;
}
