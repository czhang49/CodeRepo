/**
 * @file dl_list_provided.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "dl_list.h"

namespace cs225
{

template <class T>
dl_list<T>::node::node(T elem)
    : next{nullptr}, prev{nullptr}, data{std::move(elem)}
{
    // nothing
}

/// @cond STAFF
template <class T>
template <class Iter>
dl_list<T>::dl_list(Iter first, Iter last)
    : dl_list{}
{
    for (; first != last; ++first)
        push_back(*first);
}
/// @endcond

template <class T>
uint64_t dl_list<T>::size() const
{
    return size_;
}

/// @cond STAFF
// printing stuff
template <class T>
void dl_list<T>::print(std::ostream& stream) const
{
    stream << "<";
    for (auto curr = head_.get(); curr != nullptr; curr = curr->next.get())
        stream << " " << curr->data;
    stream << " >";
}

template <class T>
void dl_list<T>::print_reverse(std::ostream& stream) const
{
    stream << "<";
    for (auto curr = tail_; curr != nullptr; curr = curr->prev)
        stream << " " << curr->data;
    stream << " >";
}
/// @endcond

template <class T>
std::ostream& operator<<(std::ostream& stream, const dl_list<T>& list)
{
    list.print(stream);
    return stream;
}

/// @cond STAFF
// iteration
template <class T>
auto dl_list<T>::begin() const -> iterator
{
    return {head_.get()};
}

template <class T>
auto dl_list<T>::end() const -> iterator
{
    return {};
}

template <class T>
auto dl_list<T>::rbegin() const -> reverse_iterator
{
    return {tail_};
}

template <class T>
auto dl_list<T>::rend() const -> reverse_iterator
{
    return {};
}

template <class T>
dl_list<T>::iterator::iterator()
    : curr_{nullptr}
{
    // nothing
}

template <class T>
dl_list<T>::iterator::iterator(node* curr)
    : curr_{curr}
{
    // nothing
}

template <class T>
auto dl_list<T>::iterator::operator++() -> iterator &
{
    curr_ = curr_->next.get();
    return *this;
}

template <class T>
auto dl_list<T>::iterator::operator++(int) -> iterator
{
    iterator ret{*this};
    ++(*this);
    return ret;
}

template <class T>
auto dl_list<T>::iterator::operator--() -> iterator &
{
    curr_ = curr_->prev;
    return *this;
}

template <class T>
auto dl_list<T>::iterator::operator--(int) -> iterator
{
    iterator ret{*this};
    --(*this);
    return ret;
}

template <class T>
const T& dl_list<T>::iterator::operator*() const
{
    return curr_->data;
}

template <class T>
const T* dl_list<T>::iterator::operator->() const
{
    return &curr_->data;
}

template <class T>
bool dl_list<T>::iterator::operator==(const iterator& other) const
{
    return curr_ == other.curr_;
}

template <class T>
bool dl_list<T>::iterator::operator!=(const iterator& other) const
{
    return curr_ != other.curr_;
}

template <class T>
dl_list<T>::reverse_iterator::reverse_iterator()
    : curr_{nullptr}
{
    // nothing
}

template <class T>
dl_list<T>::reverse_iterator::reverse_iterator(node* curr)
    : curr_{curr}
{
    // nothing
}

template <class T>
auto dl_list<T>::reverse_iterator::operator++() -> reverse_iterator &
{
    curr_ = curr_->prev;
    return *this;
}

template <class T>
auto dl_list<T>::reverse_iterator::operator++(int) -> reverse_iterator
{
    reverse_iterator ret{*this};
    ++(*this);
    return ret;
}

template <class T>
auto dl_list<T>::reverse_iterator::operator--() -> reverse_iterator &
{
    curr_ = curr_->next.get();
    return *this;
}

template <class T>
auto dl_list<T>::reverse_iterator::operator--(int) -> reverse_iterator
{
    reverse_iterator ret{*this};
    --(*this);
    return ret;
}

template <class T>
const T& dl_list<T>::reverse_iterator::operator*() const
{
    return curr_->data;
}

template <class T>
const T* dl_list<T>::reverse_iterator::operator->() const
{
    return &curr_->data;
}

template <class T>
bool dl_list<T>::reverse_iterator::
    operator==(const reverse_iterator& other) const
{
    return curr_ == other.curr_;
}

template <class T>
bool dl_list<T>::reverse_iterator::
    operator!=(const reverse_iterator& other) const
{
    return curr_ != other.curr_;
}
/// @endcond
}
