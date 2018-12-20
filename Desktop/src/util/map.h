//
// Created by Vladyslav Yazykov on 12/12/2018.
//

#ifndef ASCENSION_ID_LIST_H
#define ASCENSION_ID_LIST_H

#include <cstring>
#include <limits>
#include "code_organizers.h"
#include "proxy.h"

template<typename V, typename K = int>
class map {
public:

public:
    struct Node;

    static constexpr unsigned char children_count{std::numeric_limits<unsigned char>::max()};
    typedef Node *nodes[children_count];

    struct Node {
        static void nullify(nodes *_n) {
            i_range(0, children_count) {
                (*_n)[i] = nullptr;
            }
        }

        nodes children;
        V *data;

        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(const Node &) = delete;
        Node &operator=(Node &&) = delete;

        inline Node() : data{nullptr} { nullify(&children); }
        inline explicit Node(const V &data) : data{new V(data)} { nullify(&children); }

        /// Recursive remove
        void remove(const char *key, size_t length) {
            if (!length) {
                delete (data);
                data = nullptr;
            } else {
                const char k = *key;
                if (!children[k]) return;
                children[k]->remove(key + 1, length - 1);
            }
        }

        /// Recursive get value pointer
        virtual Node *get(const char *key, size_t length) {
            if (!length) {
                return this;
            } else {
                const char k = *key;
                if (!children[k]) children[k] = new Node();
                return children[k]->get(key + 1, length - 1);
            }
        }

        /// For each function
        /// \param f Function or functor
        template<typename F>
        void for_each(const F &f) {
            for (Node *n: children) if (n) n->for_each(f);
            if (data) f(*data);
        }

        /// For each function, that provides iterator
        /// \param f Function or functor
        template<typename F>
        void for_each_indexed(const F &f) {
            for (Node *n: children) if (n) n->for_each_indexed(f);
            if (data) f(*data, this);
        }

        virtual ~Node() {
            for (Node *n: children) {
                delete n;
            }
            delete data;
        }
    };

private:
    Node *root{new Node()};

public:
    using prx = Proxy<Node, V>;

#define key_arg (const char *) &key, sizeof(key)
    inline virtual ~map() { delete root; }
    inline void remove(const K &key) { root->remove(key_arg); }
    inline prx operator[](const K &key) { return prx{root->get(key_arg)}; }
    inline prx operator[](const char *key) { return prx{root->get(key, strlen(key))}; }
#undef key_arg

    /// For each function
    /// \param f Function or functor
    template<typename F>
    inline void for_each(const F &f) { root->for_each(f); }

    /// For each function, that provides iterator
    /// \param f Function or functor
    template<typename F>
    inline void for_each_indexed(const F &f) { root->for_each_indexed(f); }

};


#endif //ASCENSION_ID_LIST_H
