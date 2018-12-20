//
// Created by Vladyslav Yazykov on 16/12/2018.
//

#ifndef ASCENSION_LINKED_MAP_H
#define ASCENSION_LINKED_MAP_H

#include <cstdio>
#include "map.h"

template<typename V, typename K = int>
class linked_map {

    using map = map<V, K>;

    struct Node;


    Node *root{new Node()};
    Node *endp{root};

    struct Node {
        using Base = typename map::Node;
        typedef Node *nodes[map::children_count];

        nodes children;
        V *data{nullptr};
        Node *next{nullptr}, *previous{nullptr};

        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(const Node &) = delete;
        Node &operator=(Node &&) = delete;

        inline Node() = default;
        inline explicit Node(const V &data) : data{new V(data)} {}

        /// Remove itself
        void remove() {
            delete (data);
            data = nullptr;
            previous->next = next;
            if (next) next->previous = previous;
            previous = next = nullptr;
        };

        /// Recursive remove
        void remove(const char *key, size_t length) {
            if (!length) {
                remove();
            } else {
                const char k = *key;
                if (!children[k]) return;
                children[k]->remove(key + 1, length - 1);
            }
        }

        /// Recursive get value pointer
        Node *get(const char *key, size_t length) {
            if (!length) {
                return this;
            } else {
                const char k = *key;
                if (!children[k]) children[k] = new Node();
                return children[k]->get(key + 1, length - 1);
            }
        }

        virtual ~Node() {
            delete data;
            delete next;
        }
    };


public:
    typedef Node iterator;
    using prx = Proxy<Node, V>;


#define key_arg (const char *) &key, sizeof(key)
    inline virtual ~linked_map() { delete root; }
    inline void remove(const K &key) { root->remove(key_arg); }
    void remove(Node *node) {
        if (node == endp) endp = node->previous;
        node->remove();
    }
    prx operator[](const K &key) {
        Node *res = root->get(key_arg);
        for (Node *p = root->next; p; p = p->next)
            if (p == res) {
                return prx{res};
            }
        endp->next = res;
        res->previous = endp;
        return prx{endp = res};
    }
    prx operator[](const char *key) {
        Node *res = root->get(key, strlen(key));
        for (Node *p = root->next; p; p = p->next)
            if (p == res) {
                return prx{res};
            }
        endp->next = res;
        res->previous = endp;
        return prx{endp = res};
    }
#undef key_arg

    size_t count() const {
        size_t i = 0;
        for (Node *p = root->next; p; p = p->next) i++;
        return i;
    }

    /// For each function
    /// \param f Function or functor
    template<typename F>
    inline void for_each(const F &f) { for (Node *i = root->next; i; i = i->next) f(*i->data); }

    /// For each function, that provides iterator
    /// \param f Function or functor
    template<typename F>
    inline void for_each_indexed(const F &f) { for (Node *i = root->next; i; i = i->next) f(*i->data, i); }
};

#endif //ASCENSION_LINKED_MAP_H
