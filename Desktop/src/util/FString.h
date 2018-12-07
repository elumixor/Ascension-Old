//
// Created by Vladyslav Yazykov on 07/12/2018.
//

#ifndef ASCENSION_FSTRING_H
#define ASCENSION_FSTRING_H

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

String format_str(CString str, const String &replace);

FString operator ""_fs(const char *literal, size_t length);

#endif //ASCENSION_FSTRING_H
