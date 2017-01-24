/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::left_child(size_t idx) const
{
	return 2*idx+1;
    /// @todo Update to return the index of the left child.
    
}

template <class T, class Compare>
size_t heap<T, Compare>::right_child(size_t idx) const
{
	return 2*idx+2;
    /// @todo Update to return the index of the left child.
    
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t idx) const
{
	return (idx-1)/2;
    /// @todo Update to return the parent index.
    return 0;
}

template <class T, class Compare>
bool heap<T, Compare>::has_child(size_t idx) const
{
	if (2*idx+1 >= elems_.size())
    /// @todo Update to return whether the node at index has a child.
    	return false;
	return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::max_priority_child(size_t idx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (2*idx+1==elems_.size()-1)
		return idx*2+1;
	else if (elems_[2*idx+1]<=elems_[2*idx+2])
		return 2*idx+1;
	else
		return 2*idx+2;
}

template <class T, class Compare>
void heap<T, Compare>::heapify_down(size_t idx)
{
	if (!has_child(idx))

		return;
	else
	{
		size_t maxchild=max_priority_child(idx);
		if (!higher_priority_(elems_[idx],elems_[maxchild]))
		{
			std::swap(elems_[idx],elems_[maxchild]);
			heapify_down(maxchild);
		}
	}
    /// @todo Implement the heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapify_up(size_t idx)
{
    if (idx == root())
        return;
    size_t parentIdx = parent(idx);
    if (higher_priority_(elems_[idx], elems_[parentIdx]))
    {
        std::swap(elems_[idx], elems_[parentIdx]);
        heapify_up(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
	for (uint64_t i=0;i<elems.size();i++)
	{
		elems_.push_back(elems[i]);
	}
	for (int i=elems.size()-1; i>=0;i--)
	{
		heapify_down(i);
	}
    /// @todo Construct a heap using the buildHeap algorithm
}

template <class T, class Compare>
void heap<T, Compare>::pop()
{
	std::swap(elems_[0],elems_[elems_.size()-1]);
	elems_.pop_back();
	heapify_down(0);
	
    /// @todo Remove the element with the highest priority.
}

template <class T, class Compare>
const T& heap<T, Compare>::peek() const
{
    /// @todo Return the element with the highest priority (do *not* remove!)
    return elems_[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(T elem)
{
	elems_.push_back(elem);
	heapify_up(elems_.size()-1);
    /// @todo Add an element to the heap
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
	return elems_.empty();
    /// @todo Determine if the heap is empty
    
}
