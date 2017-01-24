/**
 * @file quadtree_given.cpp
 * Contains functions of the quadtree class used for grading.
 */

#include "quadtree.h"

namespace cs225
{

void quadtree::print(std::ostream& out /* = cout */) const
{
    if (!root_)
        out << "Empty tree.\n";
    else
        print(out, root_.get(), 1);
}

void quadtree::print(std::ostream& out, const node* current, int level) const
{
    if (!current->northeast)
    {
        out << current->element << " at depth " << level << "\n";
        return;
    }

    // Standard preorder traversal
    print(out, current->northeast.get(), level + 1);
    print(out, current->southeast.get(), level + 1);
    print(out, current->southwest.get(), level + 1);
    print(out, current->northwest.get(), level + 1);
}
bool quadtree::operator==(const quadtree& other) const
{
    return equal(root_.get(), other.root_.get());
}

bool quadtree::equal(const node* first, const node* second) const
{
    if (!first && !second)
        return true;

    if (!first || !second)
        return false;

    if (!first->northeast && !second->northeast)
        return first->element == second->element;

    // they aren't both leaves, so recurse
    return (equal(first->northeast.get(), second->northeast.get()) &&
            equal(first->northwest.get(), second->northwest.get()) &&
            equal(first->southeast.get(), second->southeast.get()) &&
            equal(first->southwest.get(), second->southwest.get()));
}
}
