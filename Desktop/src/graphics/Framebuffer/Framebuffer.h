//
// Created by Vladyslav Yazykov on 03/12/2018.
//

#ifndef ASCENSION_FRAMEBUFFER_H
#define ASCENSION_FRAMEBUFFER_H

#include <code_organizers.h>

NAMESPACE(ASC, GRAPHICS)
        class Framebuffer {
            unsigned int framebuffer;
            unsigned int texColorBuffer;
        public:
            Framebuffer();
            explicit Framebuffer(float opacity) : Framebuffer() {
                    this->opacity = opacity;
            }

            virtual ~Framebuffer() = default;

            void write() const;

            void render() const;

            mutable float opacity{1.f};
        };
N2


#endif //ASCENSION_FRAMEBUFFER_H
