/**
 * @file scoped_array.tcc
 * @author Chen Zhang
 * @date Summer 2014
 */

#include <iostream>
#include"scoped_array.h"

namespace cs225
{
template <class T>
cs225::scoped_array<T>::scoped_array()
{
	size_=0;
	arr_=nullptr;
}

template <class T>
cs225::scoped_array<T>::scoped_array(uint64_t sze)
{
	
	size_=sze;
	if (sze!=0)
		arr_=new T[sze];
	else 
		arr_=nullptr;
}

template<class T>
cs225::scoped_array<T>::scoped_array(const scoped_array<T>& other)
{
	size_=other.size_;
	arr_=new T[other.size_];
	for(uint64_t i=0;i<other.size_;i++)
	{	
		arr_[i]=other.arr_[i];
	}
}

template<class T>
cs225::scoped_array<T>::scoped_array(scoped_array<T>&& other)
{
	
	size_=0;
	arr_=nullptr;

	swap(other);   
 }

template<class T>
cs225::scoped_array<T>::~scoped_array()
{
	clear();
}

template <class T>
scoped_array<T>& cs225::scoped_array<T>::operator=(scoped_array<T> rhs)
{	std::cout<<"The = operator in scoped_array is called"<<std::endl;
	swap(rhs);
	return (*this);
}

template <class T>
void cs225::scoped_array<T>::clear()
{	
	size_=0;
	delete[] arr_;  // try this part with and without []
	arr_=nullptr;
}

template <class T>
void cs225::scoped_array<T>::swap(scoped_array<T>& other)
{	
	std::swap(arr_,other.arr_);
	std::swap(size_,other.size_);
	
}

template <class T>
void cs225::scoped_array<T>::resize(uint64_t sze)
{
	scoped_array temp{sze};
	if (sze<=size_)
	{	for(uint64_t i=0;i<sze;i++)
		{
			temp.arr_[i]=arr_[i];
		}
	}
	else
	{	for(uint64_t i=0;i<size_;i++)
		{
			temp.arr_[i]=arr_[i];
		}
	}

	swap(temp);
}
 
template <class T>
const T& cs225::scoped_array<T>::operator[](uint64_t idx) const
{
	return arr_[idx];
}

template <class T>
T& cs225::scoped_array<T>::operator[](uint64_t idx)
{
	return arr_[idx];
}
}

template <class T>
const T& cs225::scoped_array<T>::at(uint64_t idx)const
{
	if (size_<=idx)
	{	
		throw std::out_of_range("Damm");
	}
	else 
	{
		return arr_[idx];
	}

}

template<class T>
T& cs225::scoped_array<T>::at(uint64_t idx) 
{
	if(size_<=idx)
	{
		throw std::out_of_range("Damm");
	}
	else
	{
		return arr_[idx];
	}
}

template<class T>
uint64_t cs225::scoped_array<T>::size()const
{
	return size_;
}

template<class T>
bool cs225::scoped_array<T>::empty()const
{
	return (arr_==nullptr);
}


