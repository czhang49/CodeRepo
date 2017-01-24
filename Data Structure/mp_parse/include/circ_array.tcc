/**
 * @file circ_array.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <stdexcept>
#include "circ_array.h"
#include<iostream>

namespace cs225
{
template <class T>
circ_array<T>::circ_array()
{
    /// @todo mp_parse.1
	head_=0;
	end_=0;
	size_=0;
	capacity_=0;
	arr_=nullptr;
}

template <class T>
circ_array<T>::circ_array(uint64_t size)
{
    if (size!=0)
	{
		arr_=nullptr;
		arr_.reset(new T[size]);
		size_=size;
		capacity_=size;
		head_=0;
		end_=size-1;
	}
	else
	{
		arr_=nullptr;
		size_=0;
		capacity_=0;
		head_=0;
		end_=0;
	}
	/// @todo mp_parse.1
}

template <class T>
circ_array<T>::circ_array(const circ_array& other)
{
	if (other.capacity_!=0)
	{
		arr_=nullptr;
		arr_.reset(new T[other.capacity_]);
	}
	else 
		arr_=nullptr;
	
	head_=other.head_;
	end_=other.end_;
	size_=other.size_;
	capacity_=other.capacity_;
/*	if (end_>=head_)
 	{
		for(uint64_t i=other.head_;i<=other.end_;i++)
		{
			arr_[i]=other.arr_[i];
		}
	}
	else
	{
		for(uint64_t i=0;i<=other.end_;i++)
		{
			arr_[i]=other.arr_[i];
		}
		for(uint64_t i=other.head_;i<other.capacity_;i++)
		{
			arr_[i]=other.arr_[i];
		}
	}*/
	for(uint64_t i=0;i<other.capacity_;i++)
		arr_.at(i)=other.arr_.at(i);   
	/// @todo mp_parse.1
}

template <class T>
circ_array<T>::circ_array(circ_array&& other)
{
	size_=0;
	capacity_=0;
	head_=0;
	end_=0;
	arr_=nullptr;
	swap(other);
    /// @todo mp_parse.1
}

template<class T>
void circ_array<T>::swap(circ_array& other)
{
	std::swap(capacity_,other.capacity_);
	std::swap(head_,other.head_);
	std::swap(end_,other.end_);
	std::swap(size_,other.size_);
	arr_.swap(other.arr_);
}
template <class T>
circ_array<T>& circ_array<T>::operator=(circ_array rhs)
{
   	swap(rhs);
	return (*this); 
	/// @todo mp_parse.1
}

template <class T>
circ_array<T>::~circ_array() = default;

template <class T>
const T& circ_array<T>::operator[](uint64_t idx) const
{
	/*if (head_<=end_)
		return arr_[idx+head_];
	else
	{
		if (idx+head_ <capacity_)
			return arr_[idx+head_];
		else
		{
			return arr_[idx-(capacity_-head_)-1];
		}
	}*/
	return arr_[getindex(idx)];
    /// @todo mp_parse.1
}

template <class T>
T& circ_array<T>::operator[](uint64_t idx)
{
	    /// @todo mp_parse.1
	/*if (head_<=end_)
		return arr_[idx+head_];
	else
	{
		if (idx+head_ <capacity_)
			return arr_[idx+head_];
		else
		{
			return arr_[idx-(capacity_-head_)-1];
		}
	}*/
	return arr_[getindex(idx)];
}

template <class T>
const T& circ_array<T>::at(uint64_t idx) const
{

	/*if (head_<=end_)
	{
		if(idx<head_ || idx>end_)
			throw std::out_of_range("Out of range at at() const function");
    }
	else
	{
		if(idx>end_ && idx<head_)
			throw std::out_of_range("Out of range at at() const function");
	}*/
	if (idx>=size_)
		throw std::out_of_range("Out of range at at() const function");
	return arr_[getindex(idx)];
	/// @todo mp_parse.1
}

template <class T>
T& circ_array<T>::at(uint64_t idx)
{

	/*if (head_<=end_)
	{
		if(idx<head_ || idx>end_)
			throw std::out_of_range("Out of range at at() const function");
    }
	else
	{
		if(idx>end_ && idx<head_)
			throw std::out_of_range("Out of range at at() const function");
	}*/
	if (idx>=size_)
		throw std::out_of_range("Out of range at at() const function");
//	std::cout<<head_<<" "<<end_<<" "<<size_<<" "<<capacity_<<"Non const at called"<<getindex(idx)<<std::endl;
	return arr_[getindex(idx)];
	/// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_front(const T& elem)
{
	if (filled())
		recapacity();
	if (head_==0)
	{
		head_=capacity_-1;	
	}
	else
	{
		head_=head_-1;
	}
	arr_[head_]=elem;
	size_=size_+1;
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_front(T&& elem)
{
	if (filled())
		recapacity();
	if (head_==0)
	{
		head_=capacity_-1;	
	}
	else
	{
		head_=head_-1;
	}
	arr_[head_]=std::move(elem);
	size_=size_+1;
	
 	/// @todo mp_parse.1
}

template <class T>
void circ_array<T>::recapacity()
{
	std::unique_ptr<T[]> temp=nullptr;
	if (capacity_==0)
	{
		temp.reset(new T[1]);
		head_=0;
		end_=0;
		capacity_=1;
		size_=0;
	}
	else
	{
		temp.reset(new T[capacity_*2]);
		uint64_t newhead=1;
		uint64_t newend=newhead+capacity_-1;
		if (head_==0 && end_==capacity_-1)
		{	
			for(uint64_t i=0;i<capacity_;i++)
			{
				temp[i+newhead]=std::move(arr_[i]);
			}
		}
		else
		{
			uint64_t keepmiddle;
			for(uint64_t i=0;(i+head_)<capacity_;i++)
			{
				temp[i+newhead]=std::move(arr_[i+head_]);
				keepmiddle=i+newhead;
			}
		
			for(uint64_t i=0;i<=end_;i++)
			{
				temp[i+keepmiddle+1]=std::move(arr_[i]);
			}
		}
			capacity_=capacity_*2;
			head_=newhead;
			end_=newend;
	}	
	arr_.reset(nullptr);
	arr_=std::move(temp);	

}
template <class T>
void circ_array<T>::push_back(const T& elem)
{
	if (filled())
		recapacity();
	if (end_==capacity_-1)
		end_=0;
	else
		end_=end_+1;
	
	arr_[end_]=elem;
	size_=size_+1;
	
    /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::push_back(T&& elem)
{
	if (filled())
	{	
		recapacity();
//		std::cout<<"recapacity called"<<head_<<" "<<end_<<" "<<size_<<" "<<capacity_<<std::endl;
	}
	if (end_==capacity_-1)
		end_=0;
	else
	{
		end_=end_+1;
	}	
	arr_[end_]=std::move(elem);
	size_=size_+1;
    /// @todo mp_parse.1
//	std::cout<<"the positions are"<<head_<<" "<<end_<<" "<<size_<<" "<<capacity_<<std::endl;
}

template <class T>
void circ_array<T>::pop_front()
{
	if(size_==1)
	{
		head_=0;	
		end_=0;
	}
	else if (head_!=capacity_-1)
		head_=head_+1;
	else
	{
		head_=0;
	}
    size_=size_-1;
	/// @todo mp_parse.1
}

template <class T>
void circ_array<T>::pop_back()
{
	if(size_==1)
	{
		head_=0;
		end_=0;
	}
	if(end_!=0)
		end_=end_-1;
	else
		end_=capacity_-1;
   size_=size_-1;
//	std::cout<<"pop back"<<head_<<" "<<end_<<" "<<size_<<" "<<capacity_<<std::endl;
	 /// @todo mp_parse.1
}

template <class T>
void circ_array<T>::erase(uint64_t idx)
{
	if (size_>1)
	{
		std::unique_ptr<T[]> temp=nullptr;
		temp.reset(new T[capacity_]);
		uint64_t index=getindex(idx);
		for(uint64_t i=0;i<index;i++)
		{
			temp[i]=std::move(arr_[i]);
		}	
		for(uint64_t i=index;i<capacity_-1;i++)
		{
			temp[i]=std::move(arr_[i+1]);
		}
		if(end_!=0)
			end_=end_-1;
		else
			end_=capacity_-1;
		size_=size_-1;
		arr_.reset(nullptr);
		arr_=std::move(temp);
	}
	else if (size_==1)
	{
		head_=0;
		end_=0;
		size_=0;
	}
}

template <class T>
uint64_t circ_array<T>::getindex(uint64_t idx) const
{
	if (head_<=end_)
		return idx+head_;
	else
	{
		if (idx+head_ <capacity_)
			return idx+head_;
		else
		{
			return (idx-(capacity_-head_));
		}
	}

}

template <class T>
uint64_t circ_array<T>::size() const
{
	return size_; 
   /// @todo mp_parse.1
}

template <class T>
bool circ_array<T>::empty() const
{
	if (size_==0)
		return true;
	else 
		return false;
    /// @todo mp_parse.1
}

template <class T>
bool circ_array<T>::filled() const
{
	if (capacity_==0 )
		return true;
	/*if (head_==0 && end_==capacity_-1)
		return true;
	if (head_-1==end_)
		return true;*/
	else if(size_==capacity_)
		return true;
	
	return false;
}
}
