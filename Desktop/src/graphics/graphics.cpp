//
// Created by Vladyslav Yazykov on 05/09/2018.
//

#include <constants/constants.h>
#include "graphics.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

Globals ASC::GRAPHICS::globals{{0.0, 0.0},
                               {0.0, 0.0}};

Matrices ASC::GRAPHICS::matrices{};

std::map<std::string, unsigned> ASC::GRAPHICS::resources{};

void Globals::update() {
    glfwGetCursorPos(GL::window, &globals.cursor.x, &globals.cursor.y);

    double currentFrame = glfwGetTime();
    globals.delta = currentFrame - globals.elapsed;
    globals.elapsed = currentFrame;
}

void Matrices::set(unsigned prog) {
//    set(UNIFORMS::MATRICES::projection, projection);
//    set(UNIFORMS::MATRICES::view, view);
//    set(UNIFORMS::MATRICES::model, model);
}