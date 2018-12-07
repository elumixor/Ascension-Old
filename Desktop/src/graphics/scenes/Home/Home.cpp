//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#include "Home.h"
#include <graphics/resources/elements.h>
#include <graphics/resources/objects/GradientBackgorund/GradientBackground.h>
#include <graphics/Mainframe/Mainframe.h>
#include <graphics/scenes/overlays/Modules.h>
#include <graphics/scenes/keys/keys.h>
#include <graphics/animation/animation.h>

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
    figure->position = glm::vec3{2.f, 0.f, 0.f};
}

Animation *animation{nullptr};
Animation *animation2{nullptr};

float angle = 0.f;

void SCENES::Home::render() {
    glDisable(GL_DEPTH_TEST);

    USE_PROGRAM(bg_shader);
    background->render();

    glEnable(GL_DEPTH_TEST);


    USE_PROGRAM(fg_shader);
    ASC::GRAPHICS::globals.matrices.set();

    figure->model *= glm::rotate(glm::mat4{1.f}, 0.4f * (float) globals.delta, {angle, 1.0f, 0.1f});
    figure->render();


    PRESS(LEFT_CONTROL, M) {
        Animation::start(&animation, &figure->position, glm::vec3{3.f, 0.f, -0.5f}, 1.f);
        printf("%p\n", animation);
//        Animation::start(&animation2, &angle, 1.f, 5.f);
        globals.mainframe->overlay = Modules::instance();
    }
    RELEASE(LEFT_CONTROL, M) {
//        animation->stop();
//        Animation::start(animation, &figure->position, glm::vec3{2.f, 0.f, 0.f}, 1.f);
        printf("%p\n", animation);
        animation->reverse();
//        animation2->reverse();
        globals.mainframe->overlay = nullptr;
    }
}

