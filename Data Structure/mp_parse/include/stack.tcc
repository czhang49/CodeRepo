/**
 * @file stack.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "stack.h"

namespace cs225
{

template <class T>
const T& stack<T>::top() const
{
	return arr_.at(arr_.size()-1);
    /// @todo mp_parse.2
}

template <class T>
T& stack<T>::top()
{
	return arr_.at(arr_.size()-1);
    /// @todo mp_parse.2
}

template <class T>
void stack<T>::push(const T& elem)
{
	arr_.push_back(elem);
    /// @todo mp_parse.2
}

template <class T>
void stack<T>::push(T&& elem)
{
	arr_.push_back(std::move(elem));
    /// @todo mp_parse.2
}

template <class T>
void stack<T>::pop()
{
   	arr_.pop_back();
	 /// @todo mp_parse.2
}

template <class T>
uint64_t stack<T>::size() const
{
	return arr_.size();
    /// @todo mp_parse.2
}

template <class T>
bool stack<T>::empty() const
{
    return arr_.empty();
	/// @todo mp_parse.2
}
}
