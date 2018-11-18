//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_HOME_H
#define ASCENSION_HOME_H

#include <graphics/scenes/Base.h>
#include <code_organizers.h>
#include <graphics/resources/objects/GradientBackgorund/GradientBackground.h>

NAMESPACE(ASC, GRAPHICS, SCENES)
            class Home : public Base {
                Home();

                ASC::GRAPHICS::RESOURCES::GradientBackground *background{nullptr};
                unsigned shader{0};
            public:
                static Home *instance();

                void render() override;
            };
N3

#endif //ASCENSION_HOME_H
