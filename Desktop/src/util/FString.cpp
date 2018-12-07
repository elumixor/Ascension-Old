//
// Created by Vladyslav Yazykov on 07/12/2018.
//

#include "FString.h"

FString::FString(const String &str) {
    size_t previous;
    size_t last;
    for (previous = last = 0; last < str.length() - 1;) {
        if (str[last++] == '%' && str[last++] == 's') {
            strings.push_back(str.substr(previous, last - 2 - previous));
            previous = last;
        }
    }
    strings.push_back(str.substr(previous, str.length() - previous));
}

FString FString::operator%(const String &replace) {
    if (strings.size() >= 2) {
        FString fs{};
        fs.strings.push_back(strings[0] + replace + strings[1]);
        for (size_t i = 2; i < strings.size(); ++i)
            fs.strings.push_back(strings[i]);
        return fs;
    }

    FString fs{};
    fs.strings = strings;
    return fs;
}

String FString::operator%=(const String &replace) {
    return (*this % replace).str();
}

FString::FString(const FString &other) {
    static unsigned count{0};
}

String FString::str() const {
    String s{};
    for (int i = 0; i < strings.size(); ++i) {
        s += strings[i] + (i == strings.size() - 1 ? "" : "%s");
    }
    return s;
}

FString::operator CString() const {
    return str().c_str();
}

CString FString::c_str() const {
    auto s = str();
    return s.c_str();
}

void FString::display() const {
    for (const auto &s : strings)
        printf(": %s\n", s.c_str());
}


String format_str(CString str, const String &replace) {
    return (FString(str) % replace).str();
}

FString operator ""_fs(const char *literal, size_t length) {
    return FString(literal);
}