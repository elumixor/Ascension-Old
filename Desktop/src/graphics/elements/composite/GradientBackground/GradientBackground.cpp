//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#include <GL/glew.h>
#include <graphics/graphics.h>
#include <constants/constants.h>
#include "GradientBackground.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

static unsigned program;
static unsigned VAO;

ELEMENTS::COMPOSITE::GradientBackground::GradientBackground(unsigned count, const Point *pts): count{count} {
    static unsigned prog{resources[RESOURCES::PROGRAM::gradient_background]
                                 = PROGRAM::create(PATHS::PROGRAM::gradient_background[0],
                                                   PATHS::PROGRAM::gradient_background[1],
                                                   PATHS::PROGRAM::gradient_background[2])};

    program = prog;
    unsigned points_count = count < CONSTRAINTS::gradient_points_max ? count
                                                                     : CONSTRAINTS::gradient_points_max;

    points = new Point[points_count];

    for (unsigned i = 0; i < points_count; i++) {
        points[i] = pts[i];
    }

    glDeleteVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO);
}

ELEMENTS::COMPOSITE::GradientBackground::~GradientBackground() {
    delete[] points;
}

void ELEMENTS::COMPOSITE::GradientBackground::render() const {
    // set uniforms
    PROGRAM::use(program);
    PROGRAM::Uniform::set_int(UNIFORMS::GRB::points_count, count, program);

    for (unsigned i = 0; i < count; i++) {
        points[i].radius += std::sin(globals.elapsed)/10.f;
    }
    PROGRAM::Uniform::set_array<Point>(UNIFORMS::GRB::points, count, points, program);

    // draw single point
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
}
