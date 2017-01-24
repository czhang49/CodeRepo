/**
 * @file scoped_ptr.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#ifndef CS225_SCOPED_PTR_H_
#define CS225_SCOPED_PTR_H_

namespace cs225
{

/**
 * The scoped_ptr is a basic RAII class for managing individual pointers to
 * heap memory. When constructed, the class "takes ownership" of the
 * pointer given to it, and the resource (memory) will be released upon the
 * destruction of this class.
 */
template <class T>
class scoped_ptr
{
  public:
    /**
     * Default constructed scoped_ptrs should point at nullptr (and thus
     * are considered "empty").
     */
    scoped_ptr();

    /**
     * Constructing a scoped_ptr from a "raw pointer" causes the
     * scoped_ptr to take ownership of that pointer. This ensures that,
     * when the scoped_ptr is destroyed, the memory associated with its
     * owned pointer is freed via a call to `delete`.
     *
     * @param rawptr The pointer to take ownership of
     */
    scoped_ptr(T* rawptr);

    /**
     * Copy constructing scoped_ptrs is not allowed. Doing so would cause
     * two pointers to be "owning" the same memory, eventually leading to a
     * double free/heap corruption error.
     */
    scoped_ptr(const scoped_ptr&) = delete;

    /**
     * Move constructing scoped_ptrs is allowed, but only if they share
     * the same underlying type `T`. This constructor will "steal the guts"
     * of the parameter, leaving it empty.
     *
     * @param other The parameter to move from; to be left empty
     */
    scoped_ptr(scoped_ptr&& other);

    /**
     * Copy assignment is disallowed for scoped_ptrs for the same reasons
     * copy construction is disallowed.
     */
    scoped_ptr& operator=(const scoped_ptr&) = delete;

    /**
     * Move assignment is similar to move construction. The parameter
     * should be left empty, and the current scoped_ptr should take
     * ownership of the parameter's underlying memory.
     *
     * Be careful and consider what you should do when the current
     * scoped_ptr is not empty!
     *
     * @param other The parameter to move from
     * @return a reference to the current object
     */
    scoped_ptr& operator=(scoped_ptr&& other);

    /**
     * The destructor for scoped_ptr should ensure that the underlying
     * pointer is freed via a call to `delete`.
     */
    ~scoped_ptr();

    /**
     * Clears the current scoped_ptr, freeing any resources it owns (if
     * any).
     */
    void clear();

    /**
     * Swaps with another scoped_ptr.
     *
     * @param other The scoped_ptr to swap with
     */
    void swap(scoped_ptr& other);

    /**
     * @return whether the scoped_ptr owns valid memory or is empty
     */
    bool empty() const;

    /**
     * "Dereference operator" used to access the underlying object owned
     * by this scoped_ptr.
     *
     * @return a const reference to the owned object
     */
    const T& operator*() const;

    /**
     * "Dereference operator" used to access the underlying object owned
     * by this scoped_ptr.
     *
     * @return a reference to the owned object
     */
    T& operator*();

    /**
     * Const member access operator: allows members to be accessed on the
     * underlying object, as in a raw pointer:
     *
     * ~~~cpp
     * rgba_pixel* r = new rgba_pixel{100, 200, 50};
     * assert(r->red == 100);
     * delete r;
     *
     * // same as
     * scoped_ptr<rgba_pixel> r{new rgba_pixel{100, 200, 50}};
     * assert(r->red = 100);
     * ~~~
     *
     * @return A const pointer to the underlying object
     */
    const T* operator->() const;

    /**
     * Member access operator: allows members to be accessed on the
     * underlying object, as in a raw pointer:
     *
     * ~~~cpp
     * rgba_pixel* r = new rgba_pixel{100, 200, 50};
     * r->red = 20;
     * delete r;
     *
     * // same as
     * scoped_ptr<rgba_pixel> r{new rgba_pixel{100, 200, 50}};
     * r->red = 20;
     * ~~~
     *
     * @return A pointer to the underlying object
     */
    T* operator->();

    /**
     * @return the raw pointer (to const) being managed, which can only be
     * *observed* by the client
     */
    const T* get() const;

    /**
     * @return the raw pointer being managed, which can only be *observed*
     * by the client
     */
    T* get();

  private:
    T* ptr_; /// The pointer to the owned object (or nullptr if empty)
};
}
#include "scoped_ptr.tcc"
#endif
