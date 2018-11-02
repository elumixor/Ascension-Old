//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_HOME_H
#define ASCENSION_HOME_H

#include <graphics/scenes/Base/Base.h>
#include <graphics/elements/composite/GradientBackground/GradientBackground.h>
#include <graphics/elements/Mesh/Mesh.h>

namespace ASC {
    namespace GRAPHICS {
        namespace SCENES {

            class Home : public ASC::GRAPHICS::SCENES::Base {
            private:
                Home();

                const unsigned &program;

                ELEMENTS::COMPOSITE::GradientBackground background;
                ELEMENTS::Mesh mesh;

                glm::mat4 model;
                glm::vec3 translation;
            public:
                Home(const Home &) = delete;

                void operator=(const Home &) = delete;

                static Home *instance();

                void render() override;
            };
        }
    }
}

#endif //ASCENSION_HOME_H
