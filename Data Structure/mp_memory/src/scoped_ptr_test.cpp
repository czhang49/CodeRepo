/**
 * @file scoped_ptr_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "scoped_ptr.h"
#include <cassert>
#include <type_traits>
#include <memory>

using namespace cs225;

void test_empty_ptrs()
{
    scoped_ptr<int> emptyptr;
    assert(emptyptr.empty());

    scoped_ptr<double> emptyptr2{nullptr};
    assert(emptyptr.empty());
}

void test_full_ptr()
{
    scoped_ptr<int> ptr1{new int{1}};
    assert(!ptr1.empty());
    assert(*ptr1 == 1);
}

void test_const_deref()
{
    const scoped_ptr<int> ptr{new int{2}};
    assert(*ptr == 2);

    static_assert(!std::is_const<decltype(*ptr)>::value,
                  "scoped_ptr::operator*() const should return a const ref!");
}

void test_deref()
{
    scoped_ptr<int> ptr{new int{6}};
    assert(*ptr == 6);

    *ptr = 2;
    assert(*ptr == 2);
}

void test_no_copy_construction()
{
    static_assert(!std::is_copy_constructible<scoped_ptr<float>>::value,
                  "scoped_ptr should not be copy constructable!");
}

void test_no_copy_assignment()
{
    static_assert(!std::is_copy_assignable<scoped_ptr<char>>::value,
                  "scoped_ptr should not be copy is_copy_assignable!");
}

void test_move_construction()
{
    scoped_ptr<int> ptr{new int{3}};
    assert(!ptr.empty());
    assert(*ptr == 3);
    scoped_ptr<int> ptr2{std::move(ptr)};
    assert(*ptr2 == 3);
    assert(!ptr2.empty());
    assert(ptr.empty());
}

void test_move_assignment()
{
    scoped_ptr<int> ptr{new int{3}};
    assert(!ptr.empty());
    assert(*ptr == 3);
    scoped_ptr<int> ptr2{new int{5}};
    assert(!ptr2.empty());
    assert(*ptr2 == 5);

    ptr2 = std::move(ptr);
    assert(*ptr2 == 3);
    assert(!ptr2.empty());
    assert(ptr.empty());
}

int main()
{
    test_empty_ptrs();
    test_full_ptr();
    test_const_deref();
    test_deref();
    test_no_copy_construction();
    test_no_copy_assignment();
    test_move_construction();
    test_move_assignment();

    return 0;
}
