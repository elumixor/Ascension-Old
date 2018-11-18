//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#include "Home.h"
#include <graphics/resources/elements.h>
#include <graphics/resources/objects/GradientBackgorund/GradientBackground.h>

using namespace ASC::GRAPHICS;

SCENES::Home::Home() {
    background = GET_ELEMENT(GradientBackground, "home_bg");

    shader = GET_PROGRAM("gradient_background");

    background->points_count = 2;
    background->points[0] = RESOURCES::Point{{0.f, 1.f, 1.f, .3f}, {.5f, -.3f}, 3.f, 5};
    background->points[1] = RESOURCES::Point{{1.f, 0.f, 1.f, .5f}, {-.5f, .3f}, 5.1f, 6};
}

SCENES::Home *SCENES::Home::instance() {
    static Home home;
    return &home;
}

void SCENES::Home::render() {
    USE_PROGRAM(shader);
    background->render();
}
