//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_MAINFRAME_H
#define ASCENSION_MAINFRAME_H

#include <cstdio>
#include <graphics/graphics.h>
#include <graphics/scenes/Base.h>

namespace ASC {
    namespace GRAPHICS {

        /**
         *
         */
        class Mainframe {
        private:
            Mainframe();

            void process_keys();

        public:
            static Mainframe *instance();

            Mainframe(const Mainframe &) = delete;

            void operator=(const Mainframe &) = delete;

            // start main loop
            void start();

            // stop loop
            void stop() { glfwSetWindowShouldClose(GL::window, true); }

            // cleanup
            ~Mainframe();

            // pointer to an active scene
            ASC::GRAPHICS::SCENES::Base *scene{nullptr};

            // pointer to overlay scene
            ASC::GRAPHICS::SCENES::Base *overlay{nullptr};
        };

    }
}


#endif //ASCENSION_MAINFRAME_H
