//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#include "Home.h"
#include <graphics/resources/elements.h>
#include <graphics/resources/objects/GradientBackgorund/GradientBackground.h>
#include <graphics/Mainframe/Mainframe.h>
#include <graphics/scenes/overlays/Modules.h>
#include <graphics/scenes/keys/keys.h>
#include "util/util.h"

using namespace ASC::GRAPHICS;

static int counter{0};

SCENES::Home::Home() {
    background = GET_ELEMENT(GradientBackground, "home_bg");

    bg_shader = GET_PROGRAM("gradient_background");
    fg_shader = GET_PROGRAM("home");

    background->points_count = 2;
    background->points[0] = RESOURCES::Point{{0.f, 1.f, 1.f, .3f}, {.5f, -.3f}, 3.f, 5};
    background->points[1] = RESOURCES::Point{{1.f, 0.f, 1.f, .5f}, {-.5f, .3f}, 5.1f, 6};

    figure = GET_ELEMENT(Figure, "home_figure");
    figure->model = glm::translate(figure->model, glm::vec3{2.f, 0.f, 0.f});
}

void SCENES::Home::render() {

    glDisable(GL_DEPTH_TEST);

    USE_PROGRAM(bg_shader);
    background->render();

    glEnable(GL_DEPTH_TEST);


    USE_PROGRAM(fg_shader);
    ASC::GRAPHICS::globals.matrices.set();
    figure->model = glm::rotate(figure->model, 0.4f * (float) globals.delta, {0.f, 1.0f, 0.1f});
    figure->render();


    PRESS(LEFT_CONTROL, M) {
        printf("press\n");
        globals.mainframe->overlay = Modules::instance();
    }
    RELEASE(LEFT_CONTROL, M) {
        printf("release\n");
        globals.mainframe->overlay = nullptr;
    }
}
