//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#include <graphics/elements/Mesh/Mesh.h>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <graphics/graphics.h>
#include <graphics/Mainframe/Mainframe.h>
#include <graphics/scenes/ModuesOV/ModulesOV.h>
#include <graphics/scenes/Knowledge/Knowledge.h>
#include <constants/constants.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Home.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

SCENES::Home *SCENES::Home::instance() {
    static Home instance;
    return &instance;
}

SCENES::Home::Home() : program{resources[RESOURCES::PROGRAM::home] =
                                       PROGRAM::create(PATHS::PROGRAM::home[0],
                                                       PATHS::PROGRAM::home[1])},
                       background{2, (ELEMENTS::COMPOSITE::GradientBackground::Point[2]) {
                               ELEMENTS::COMPOSITE::GradientBackground::Point({0.f, 1.f, 1.f, .3f}, {.5f, -.3f}, 3.f,
                                                                              5),
                               ELEMENTS::COMPOSITE::GradientBackground::Point({1.f, 0.f, 1.f, .5f}, {-.5f, .3f}, 5.1f,
                                                                              6)
                       }},
                       mesh{PATHS::MESHES::home[0], ELEMENTS::Mesh::LOCATION},
                       model{glm::scale(glm::mat4(1.f), {.5f, .5f, .5f})} {
    model *= glm::scale(glm::vec3(.3f));
    model *= glm::translate(glm::vec3{3.0f, 0.5f, -3.5f});
}

void SCENES::Home::render() {
    // render background
    background.render();

    // render object
    PROGRAM::use(program);
    model *= glm::rotate((float)globals.delta, glm::vec3(.3f, 1.f, .4f));
    matrices.model = model;
    matrices.set();
    mesh.render();

    // render texts

    // react to input
    if (glfwGetKey(GL::window, GLFW_KEY_M) == GLFW_PRESS) {
        Mainframe::instance()->scene = SCENES::Knowledge::instance();
    }
}
