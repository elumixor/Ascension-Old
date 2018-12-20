//
// Created by Vladyslav Yazykov on 07/12/2018.
//

#ifndef ASCENSION_LITERALS_H
#define ASCENSION_LITERALS_H

#include "code_organizers.h"
#include "string"
#include "math.h"

String operator ""_s(const char *literal, size_t length) {
    return String(literal);
}

void operator ""_log(const char *literal, size_t) {
    LOG(literal);
}

#endif //ASCENSION_LITERALS_H
