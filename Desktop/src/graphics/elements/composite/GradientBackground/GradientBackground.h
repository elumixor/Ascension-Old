//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#ifndef ASCENSION_GRADIENTBACKGROUND_H
#define ASCENSION_GRADIENTBACKGROUND_H

#include "graphics/graphics.h"
#include "constants/constants.h"

namespace ASC {
    namespace GRAPHICS {
        namespace ELEMENTS {
            namespace COMPOSITE {

                class GradientBackground {
                public:
                    class Point : public ASC::GRAPHICS::PROGRAM::Uniform {
                    public:
                        glm::vec4 color;

                        glm::vec2 location;

                        float radius;

                        unsigned factor;

                        Point() : color{0.f}, location{0.f}, radius{0.f},
                                  factor{ASC::CONSTANTS::DEFAULTS::gradient_point_factor} {};

                        Point(glm::vec4 c, glm::vec2 l, float r,
                              unsigned f = ASC::CONSTANTS::DEFAULTS::gradient_point_factor) : color{c}, location{l},
                                                                                              radius{r}, factor{f} {};

                        void set(std::string name, unsigned program = PROGRAM::active) const override;

                        static constexpr size_t size = sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(float);
                    };

                private:
                    const unsigned count;
                    Point *points{nullptr};
                public:
                    explicit GradientBackground(unsigned count, const Point *pts);

                    virtual ~GradientBackground();

                    void render() const;
                };
            }
        }
    }
}


#endif //ASCENSION_GRADIENTBACKGROUND_H
