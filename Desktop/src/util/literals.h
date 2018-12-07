//
// Created by Vladyslav Yazykov on 07/12/2018.
//

#ifndef ASCENSION_LITERALS_H
#define ASCENSION_LITERALS_H

#include "code_organizers.h"
#include "string"

String operator ""_s(const char *literal, size_t length) {
    return String(literal);
}

template<char... digits>
String operator ""_s();

template<char... dd>
struct int_to_string;

template<unsigned base, unsigned p>
struct pow_struct;

template<unsigned base>
struct pow_struct<base, 1> {
    static constexpr unsigned value = base;
};

template<unsigned base, unsigned p>
struct pow_struct {
    static constexpr unsigned value = base * pow_struct<base, p - 1>::value;
};

template<char d, char... dd>
struct int_to_string<d, dd...> {
    static constexpr int value = (d - '0') * (pow_struct<10, sizeof...(dd)>::value) + int_to_string<dd...>::value;
};

template<char d>
struct int_to_string<d> {
    static constexpr int value = (d - '0');
};

template<char... digits>
String operator ""_s() {
    return std::to_string(int_to_string<digits...>::value);
}

#endif //ASCENSION_LITERALS_H
