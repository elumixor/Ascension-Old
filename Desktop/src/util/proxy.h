//
// Created by Vladyslav Yazykov on 16/12/2018.
//

#ifndef ASCENSION_PROXY_H
#define ASCENSION_PROXY_H

#include <exception>

template<typename T, typename V>
class Proxy {
    T *node;
public:
    explicit Proxy(T *node) : node{node} {}

    class not_present : public std::exception {
        const char *what() const noexcept override {
            return "Key is not present in map";
        }
    };

    Proxy &operator=(const V &value) {
        if (node->data) *node->data = value;
        else node->data = new V(value);

        return *this;
    }

    Proxy &operator=(V &&value) noexcept {
        if (node->data) node->data = &value;
        else node->data = new V(std::move(value));

        return *this;
    }

    V &value() const {
        if (!node->data) throw not_present();
        return *node->data;
    }

    inline operator V() const { return value(); }
    inline bool is_present() const { return node->data; }
};

#endif //ASCENSION_PROXY_H
