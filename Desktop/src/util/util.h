//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_UTIL_H
#define ASCENSION_UTIL_H

#include <code_organizers.h>
#include <vector>
#include "string"


class FString {
    std::vector<String> strings;

    FString() = default;

public:
    FString(const FString &other);

    explicit FString(const String &str);

    FString operator%(const String &replace);

    String operator%=(const String &replace);

    String str() const;

    operator CString() const;

    CString c_str() const;

    void display() const;
};

static const char * __get_message(const char * msg) {
    return msg;
}
static const char * __get_message(const String& msg) {
    return msg.c_str();
}

String fstr(CString str, const String &replace);

//region _s string literal

FString operator ""_fs(const char *literal, size_t length);

String operator ""_s(const char *literal, size_t length);

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
//endregion

#endif //ASCENSION_UTIL_H
