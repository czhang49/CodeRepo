/**
 * @file scoped_array.h
 * @author Chen Zhang
 * @date Summer 2014
 */

#ifndef CS225_SCOPED_ARRAY_H
#define CS225_SCOPED_ARRAY_H
#include<iostream>

namespace cs225
{
template <class T>
class scoped_array
{	
	public:
		scoped_array();
		scoped_array(uint64_t sze);
		scoped_array(const scoped_array<T>& other);
		scoped_array(scoped_array<T>&& other);
		scoped_array<T>& operator=(scoped_array<T> rhs);
		~scoped_array();
		
		void clear();
		void swap(scoped_array<T>& other);
		void resize(uint64_t size);
		
		const T& operator[](uint64_t idx)const;
		T& operator[] (uint64_t idx);
		const T& at(uint64_t idx) const;
		T& at(uint64_t idx);
		uint64_t size()const;
		bool empty() const;
	
	private:
		T* arr_;
		uint64_t size_;

};
}

#include "scoped_array.tcc"
#endif 
