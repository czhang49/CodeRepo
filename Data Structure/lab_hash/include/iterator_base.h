#ifndef ITERATOR_BASE_
#define ITERATOR_BASE_

#include <iterator>
#include <type_traits>

namespace cs225
{
/// \cond STAFF

/**
 * A CRTP base class for more easily creating iterators.
 */
template <class Category, class Value, class Iterator>
class iterator_base : public std::iterator<Category, Value>
{
  public:
    Iterator& operator++()
    {
        self()->increment();
        return *self();
    }

    Iterator operator++(int)
    {
        Iterator temp = *self();
        self()->increment();
        return temp;
    }

    const Value* operator->() const
    {
        return &self()->dereference();
    }

    const Value& operator*() const
    {
        return self()->dereference();
    }

    friend inline bool operator==(const iterator_base& lhs,
                                  const iterator_base& rhs)
    {
        return lhs.self()->equal(*rhs.self());
    }

    friend inline bool operator!=(const iterator_base& lhs,
                                  const iterator_base& rhs)
    {
        return !(lhs == rhs);
    }

  private:
    inline Iterator* self()
    {
        return static_cast<Iterator*>(this);
    }

    inline const Iterator* self() const
    {
        return static_cast<const Iterator*>(this);
    }
};
/// \endcond
}
#endif
