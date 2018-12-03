//
// Created by Vladyslav Yazykov on 30/11/2018.
//

#ifndef ASCENSION_SINGLETON_H
#define ASCENSION_SINGLETON_H

#define SINGLETON_V(name)                               \
            public:                                     \
                name(const name &) = delete;            \
                void operator=(const name &) = delete;  \

#define SINGLETON(name)                                 \
                SINGLETON_V(name)                       \
                static name *instance() {               \
                    static name instance;               \
                    return &instance;                   \
                }                                       \

template<class Class>
Class *instance() {
    static Class instance;
    return &instance;
}

#endif //ASCENSION_SINGLETON_H
