//
// Created by Vladyslav Yazykov on 05/09/2018.
//

#include <constants/constants.h>
#include "graphics.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

Globals ASC::GRAPHICS::globals{{0.0, 0.0},
                               {0.0, 0.0},
                               {},
                               {0,   0}};

std::map<std::string, unsigned> ASC::GRAPHICS::resources{};

void Globals::update() {
    glfwGetCursorPos(GL::window, &globals.cursor.x, &globals.cursor.y);

    double currentFrame = glfwGetTime();
    globals.delta = currentFrame - globals.elapsed;
    globals.elapsed = currentFrame;
}

void Globals::Matrices::set() {
    UNI_SET(projection);
    UNI_SET(view);
}