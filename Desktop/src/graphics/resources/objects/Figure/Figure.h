//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#ifndef ASCENSION_FIGURE_H
#define ASCENSION_FIGURE_H

#include <graphics/resources/objects/Base.h>
#include <graphics/resources/VAO/VAO.h>
#include <graphics/resources/elements.h>
#include <glm/gtc/matrix_transform.hpp>
#import "code_organizers.h"

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            class Figure : public Base {
                VAO *vao = GET_VAO("home_dummy", {3, 2, 3});
            public:
                glm::mat4 model{glm::scale(glm::mat4(1.f), {.5f, .5f, .5f})};

                void render(const std::string &base_name = "") const override;
            };
N3


#endif //ASCENSION_FIGURE_H
