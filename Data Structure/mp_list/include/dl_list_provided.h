/**
 * @file dl_list_provided.h
 * @author Chase Geigle
 * @date Summer 2014
 */

/**
 * @cond STAFF
 */
    template <class Iter>
    dl_list(Iter first, Iter last);

    void print(std::ostream& stream) const;
    void print_reverse(std::ostream& stream) const;

    class iterator
        : public std::iterator<std::bidirectional_iterator_tag, const T>
    {
      public:
        iterator();
        iterator(node* curr);

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        const T& operator*() const;
        const T* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

      private:
        node* curr_;
    };

    class reverse_iterator
        : public std::iterator<std::bidirectional_iterator_tag, const T>
    {
      public:
        reverse_iterator();
        reverse_iterator(node* curr);

        reverse_iterator& operator++();
        reverse_iterator operator++(int);
        reverse_iterator& operator--();
        reverse_iterator operator--(int);
        const T& operator*() const;
        const T* operator->() const;

        bool operator==(const reverse_iterator& rhs) const;
        bool operator!=(const reverse_iterator& rhs) const;

      private:
        node* curr_;
    };
    iterator begin() const;
    iterator end() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
/** @endcond */

