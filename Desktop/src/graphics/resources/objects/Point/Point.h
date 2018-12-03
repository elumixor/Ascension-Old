#ifndef ASCENSION_OBJECTS_POINT_H
#define ASCENSION_OBJECTS_POINT_H

#include "graphics/resources/objects/Base.h"
#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec2.hpp>

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            struct Point : public Base {
                glm::vec4 color{0.f};
                glm::vec2 location{0.f};
                float radius{0.f};
                int factor{0};

                Point() = default;

                Point(glm::vec4 color, glm::vec2 location, float radius, int factor) : color{color}, location{location},
                                                                                       radius{radius}, factor{factor} {}

                void render(const String &base_name = "") const override;
            };

N3
#endif //ASCENSION_OBJECTBASE_H
