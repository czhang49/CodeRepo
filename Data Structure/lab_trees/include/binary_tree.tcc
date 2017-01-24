/**
 * @file binary_tree.tcc
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include<iostream>
#include<vector>

template <class T>
int binary_tree<T>::height() const
{
    // Call recursive helper function on root
    return height(root_.get());
}

template <class T>
int binary_tree<T>::height(const node* subRoot) const
{
    // Base case
    if (!subRoot)
        return -1;

    // Recursive definition
    auto left = height(subRoot->left.get());
    auto right = height(subRoot->right.get());
    return std::max(left, right) + 1;
}

template <class T>
void binary_tree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root_.get());

    // Finish the line
    std::cout << std::endl;
}

template <class T>
void binary_tree<T>::printLeftToRight(const node* subRoot) const
{
    // Base case - null node
    if (!subRoot)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left.get());

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right.get());
}

template <class T>
void binary_tree<T>::mirror()
{
	mirror(root_.get());    /// @todo your code here
}

template <class T>
void binary_tree<T>::mirror(node* subroot)
{
	if (!subroot)
		return;
	subroot->left.swap(subroot->right);
	
	mirror(subroot->left.get());
	mirror(subroot->right.get());	
}

template <class T>
bool binary_tree<T>::isOrdered() const
{
    /// @todo your code here
    if (isOrdered(root_.get()))
		return true;
	return false;
}

template <class T>
bool binary_tree<T>::isOrdered(node* subroot) const
{
	if (!subroot)
		return true;

	if (leftisallsmall(subroot->left.get(),subroot->elem) && rightisalllarge(subroot->right.get(),subroot->elem) )
		return (isOrdered(subroot->left.get()) && isOrdered(subroot->right.get()));	
	
	return false;		
}

template <class T>
bool binary_tree<T>::leftisallsmall(node* start, T elem) const
{
	if (start==nullptr)
		return true;
	
	if (start->elem > elem)
		return false;

	return leftisallsmall(start->left.get(),elem) && leftisallsmall(start->right.get(),elem);	
}

template <class T>
bool binary_tree<T>::rightisalllarge(node* start, T elem) const
{
	if(start==nullptr)
		return true;
	if (start->elem < elem)
		return false;

	return rightisalllarge(start->left.get(),elem) && rightisalllarge(start->right.get(),elem);
}


template <class T>
void binary_tree<T>::printPaths() const
{	
	std::vector<uint64_t> prev;
	printPaths(prev,root_.get());
    /// @todo your code here
}

template <class T>
void binary_tree<T>::printPaths(std::vector<uint64_t> prev,node* subroot) const
{
	if (!subroot)
		;
	else if (!subroot->right.get() && !subroot->left.get())
	{	
		std::cout<<"Path: ";
		for(uint64_t i=0;i<prev.size();i++)	
		{	
			std::cout<<prev[i]<<" ";
		}
	
		std::cout<<subroot->elem<<std::endl;
		//return;
	}
	else 
	{
		prev.push_back(subroot->elem);
		printPaths(prev,subroot->left.get());
		printPaths(prev,subroot->right.get());		
	}
}


template <class T>
uint64_t binary_tree<T>::sumDistances() const
{
    /// @todo your code here
	if (!root_.get())
    	return -1;
	return sumDistances(-1,root_.get());
}

template <class T>
uint64_t binary_tree<T>::sumDistances(uint64_t prev,node* subroot) const
{
	
	if (!subroot)
		return -1*prev-1;
	prev=prev+1;
	return sumDistances(prev,subroot->left.get())+sumDistances(prev,subroot->right.get())+2+2*prev;
    
}
