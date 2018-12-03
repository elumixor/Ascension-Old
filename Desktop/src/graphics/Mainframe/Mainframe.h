//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_MAINFRAME_H
#define ASCENSION_MAINFRAME_H

#include <cstdio>
#include <graphics/graphics.h>
#include <graphics/scenes/SceneBase.h>

namespace ASC {
    namespace GRAPHICS {

        class Mainframe {
        private:
            void process_keys();

            Mainframe();

        SINGLETON(Mainframe)

            // start main loop
            void start();

            // stop loop
            void stop() { glfwSetWindowShouldClose(GL::window, true); }

            // cleanup
            ~Mainframe();

            // pointer to an active scene
            ASC::GRAPHICS::SCENES::SceneBase *scene{nullptr};

            // pointer to overlay scene
            ASC::GRAPHICS::SCENES::SceneBase *overlay{nullptr};
        };

    }
}


#endif //ASCENSION_MAINFRAME_H
