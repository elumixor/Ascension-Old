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
#include "util/literals.h"
#include "util/Bezier.h"

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

float progress{0.f};
Bezier<float> esn{0.f, 0.f, 2.f, 0.f};


void SCENES::Home::render() {
    glDisable(GL_DEPTH_TEST);

    USE_PROGRAM(bg_shader);
    background->render();

    glEnable(GL_DEPTH_TEST);


    USE_PROGRAM(fg_shader);
    ASC::GRAPHICS::globals.matrices.set();

    figure->model *= glm::rotate(glm::mat4{1.f}, 0.4f * (float) globals.delta, {angle, 1.0f, 0.1f});
    figure->render();

    static Bezier<glm::vec3> b{{1.f, 0.f, 1.f},
                               {2.f, 0.f, -.5f},
                               {2.f, 3.f, -.5f},
                               {3.f, 0.f, -.5f}};
    figure->position = b(progress);

    PRESS(K) {
        "K"_log;

    }
    PRESS(L) {
        "Log"_log;
    }

    PRESS(LEFT_CONTROL, M) {
        "hello"_log;
        animations.fleeting("cube", &progress, 1.f, .5f, Easings::bezier<esn>);
        Modules::instance()->fade_in();
    }
    RELEASE(LEFT_CONTROL, M) {
        animations.reverse("cube");
        Modules::instance()->fade_out();
    }
}

