/**
 * @file queue.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "queue.h"

namespace cs225
{

template <class T>
const T& queue<T>::front() const
{
	return arr_.at(0);
    /// @todo mp_parse.2
}

template <class T>
T& queue<T>::front()
{
	return arr_.at(0);
    /// @todo mp_parse.2
}

template <class T>
void queue<T>::push(const T& elem)
{
	arr_.push_back(elem);
    /// @todo mp_parse.2
}

template <class T>
void queue<T>::push(T&& elem)
{
	arr_.push_back(std::move(elem));
    /// @todo mp_parse.2
}

template <class T>
void queue<T>::pop()
{
	arr_.pop_front();
    /// @todo mp_parse.2
}

template <class T>
uint64_t queue<T>::size() const
{
	return arr_.size();
    /// @todo mp_parse.2
}

template <class T>
bool queue<T>::empty() const
{
	return arr_.empty();
    /// @todo mp_parse.2
}
}
