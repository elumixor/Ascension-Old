//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#include <cstdlib>
//#include <graphics/scenes/ModuesOV/ModulesOV.h>
#include <GL/glew.h>
#include <constants/constants.h>
#include "Mainframe.h"
#include <glm/gtc/matrix_transform.hpp>
#include <graphics/resources/elements.h>
#include <graphics/Framebuffer/Framebuffer.h>
#include <graphics/animation/animation.h>

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

/**
 * Workaround for new bugged MacOS Mojave
 */
static void position_fix() {
    unsigned init = 0;
    int x, y;
    while (init != 2) {
        glfwGetWindowPos(GL::window, &x, &y);
        glfwSetWindowPos(GL::window, x + 1, y + 1);

        init++;

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(GL::window);
        glfwPollEvents();
    }
    glfwGetWindowPos(GL::window, &x, &y);
    glfwSetWindowPos(GL::window, x - 2, y - 2);
}

Mainframe::Mainframe() {
    GL::init(PARAMS::window_width, PARAMS::window_height, PARAMS::window_title, PARAMS::vsync);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    globals.matrices.projection = glm::perspective(glm::radians(PARAMS::persepctive_zoom),
                                                   (float) PARAMS::window_width / (float) PARAMS::window_height, 0.1f,
                                                   100.0f);
    globals.matrices.view = glm::lookAt(glm::vec3{0.f, 0.f, 5.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    globals.mainframe = this;


}

Mainframe::~Mainframe() {
    glfwTerminate();
    free_animations();
}

void Mainframe::start() {
    position_fix();
    do {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // get input
        Globals::update();

        // global processing
        process_keys();

        // scenes' processing and drawing

        if (scene) scene->render();
        if (overlay) overlay->render();

        for (Animation *animation = animations; animation != nullptr; animation = animation->next())
            animation->step();

        glfwSwapBuffers(GL::window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(GL::window));
}

void Mainframe::process_keys() {
    if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        ASC::GRAPHICS::Mainframe::instance()->stop();
    }
//    if (glfwGetKey(GL::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS
//        && glfwGetKey(GL::window, GLFW_KEY_S) == GLFW_PRESS) {
//        // start transition
////        overlay = ASC::GRAPHICS::SCENES::ModulesOV::instance();
//    }
//    if (glfwGetKey(GL::window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE
//        || glfwGetKey(GL::window, GLFW_KEY_S) == GLFW_RELEASE) {
//        // sort of start transition in reverse order
//        if (overlay) {
//            overlay = nullptr;
//        }
//    }

}
