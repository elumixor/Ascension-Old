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
#include <iostream>
#include "util/literals.h"
#include "util/Bezier.h"

using namespace ASC::GRAPHICS;


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

static Bezier<float> easing{0.f, 0.f, 2.f, 0.f};

void SCENES::Home::render() {
    static float progress{0.f};
    static Bezier<glm::vec3> b{
        {1.f, 0.f, 1.f},
        {2.f, 5.f, 1.f},
                               {3.f, 0.f, -.5f}};

    glDisable(GL_DEPTH_TEST);

    USE_PROGRAM(bg_shader);
    background->render();

    glEnable(GL_DEPTH_TEST);

    background->points[0].radius = 2.f + (float)std::sin(globals.elapsed);

    static Bezier<glm::vec2> point_location{ {-1.f, .3f}, { -.4f, .3f}, {-.1f, .4f}};
    background->points[1].location = point_location(float(std::sin(globals.elapsed)));

    USE_PROGRAM(fg_shader);
    ASC::GRAPHICS::globals.matrices.set();

    figure->model *= glm::rotate(glm::mat4{1.f}, 0.4f * (float) globals.delta, {angle, 1.0f, 0.1f});
    figure->render();


    figure->position = b(progress);

    PRESS(LEFT_CONTROL, M) {
        animations.fleeting("cube", &progress, 1.f, .5f, Easings::bezier<easing>);
        Modules::instance()->fade_in();
    }
    RELEASE(LEFT_CONTROL, M) {
        animations.reverse("cube");
        Modules::instance()->fade_out();
    }
}

