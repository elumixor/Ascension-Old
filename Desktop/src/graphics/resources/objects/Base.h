//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_RES_BASE_H
#define ASCENSION_RES_BASE_H

#include <string>
#include "code_organizers.h"

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            class Base {
            public:
                virtual ~Base() = default;

                virtual void render(const String &base_name = "") const = 0;
            };
N3


#endif //ASCENSION_BASE_H
