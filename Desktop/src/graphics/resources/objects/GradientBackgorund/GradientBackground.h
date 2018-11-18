//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_GRADIENTBACKGROUND_H
#define ASCENSION_GRADIENTBACKGROUND_H

#include "graphics/resources/elements.h"
#include <code_organizers.h>
#include <graphics/resources/objects/Base.h>
#include <graphics/resources/objects/Point/Point.h>
#include <constants/constants.h>

#define GRADIENT_POINTS_MAX 5

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            class GradientBackground : public Base {
                VAO* vao = GET_VAO("home_dummy");
            public:
                unsigned points_count{0};
                Point points[GRADIENT_POINTS_MAX];

                void render(const String &base_name = "") const;
            };
N3

#endif //ASCENSION_GRADIENTBACKGROUND_H
