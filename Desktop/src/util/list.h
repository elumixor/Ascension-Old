//
// Created by Vladyslav Yazykov on 07/12/2018.
//

#ifndef ASCENSION_LIST_H
#define ASCENSION_LIST_H

#include <initializer_list>

/// Simple custom unsorted linked list
template<typename T>
class list {
protected:
    template<typename TT = T>
    struct it;

    typedef it<T> iterator;

    /// Iterator structure
    template<typename TT>
    struct it {
        typedef it<TT> iterator;

        iterator *next, *previous;
        TT *data;

        explicit it(TT *data, iterator *previous = nullptr, iterator *next = nullptr) :
                data{data}, previous{previous}, next{next} {}

        iterator &operator++() {
            if (next) {
                data = next->data;
                previous = this;
                next = next->next;
            } else {
                previous = this;
                next = nullptr;
                data = nullptr;
            }

            return *this;
        }

        inline TT &operator*() { return *data; }

        inline friend bool operator!=(iterator const &a, iterator const &b) { return a.data != b.data; }

        /// Remove element from list
        void remove() {
            delete (data);
            if (previous) previous->next = next;
            if (next) next->previous = previous;
            delete (this);
        }

        /// Add element to the end of the list
        iterator *add(const TT &t) {
            next = new iterator(new TT(t));
            next->previous = this;
            return next;
        }
    };

    iterator *_begin{nullptr};
    iterator *_end{nullptr};
public:
    //region Constructors

    list() = default;

    list(std::initializer_list<T> data) {
        for (const T &d : data) {
            add(d);
        }
    }

    //endregion

    /// Destructor
    virtual ~list() {
        iterator *i = _begin;
        while (i) {
            auto ii = i->next;
            delete i->data;
            delete i;
            i = ii;
        }
    }

    //region Add

    /// Add element to list (copy)
    iterator *add(const T &item) {
        if (!_begin) return _end = _begin = new iterator(new T(item));
        else return _end = _end->add(item);
    }

    /// Add element to list (move)
    iterator *add(T &&item) noexcept {
        if (!_begin) return _end = _begin = new iterator(new T(item));
        else return _end = _end->add(item);
    }

    //endregion

    /// Remove element from list by iterator
    void remove(iterator *i) {
        if (_begin == i) _begin = i->next;
        else if (_end == i) _end = i->previous;
        i->remove();
    }

    //region Support range for loop

    iterator begin() const noexcept { return *_begin; }

    iterator end() const noexcept { return iterator(nullptr); }

    //endregion

    /// Check if list contains any elements
    inline bool empty() const { return _begin == nullptr; }

    /// For each function
    /// \param f Function or functor
    template<typename F>
    void for_each(const F &f) {
        for (iterator *i = _begin; i != nullptr; i = i->next) {
            f(*i->data);
        }
    }

    /// Check if any element satisfies the condition
    /// \param f Predicate
    template<typename F>
    bool any(const F &f) {
        for (iterator *i = _begin; i != nullptr; i = i->next) {
            if (f(*i->data)) return true;
        }
        return false;
    }

    /// Check if all element satisfy the condition
    /// \param f Predicate
    template<typename F>
    bool all(const F &f) {
        for (iterator *i = _begin; i != nullptr; i = i->next) {
            if (!f(*i->data)) return false;
        }
        return true;
    }

    /// Map list
    template<typename TT, typename F>
    list<TT> map(const F &f) {
        list<TT> l;
        for_each([&](T el) {
            l.add(f(el));
        });
        return l;
    }
};


#endif //ASCENSION_LIST_H
