//
// Created by Vladyslav Yazykov on 05/09/2018.
//

#include <graphics/graphics.h>
#include <string>
#include <constants/constants.h>
#include "GradientBackground.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

void ELEMENTS::COMPOSITE::GradientBackground::Point::set(std::string name, unsigned int program) const {
    PROGRAM::Uniform::set((name + "." + UNIFORMS::GRB::point_color).c_str(), color, program);
    PROGRAM::Uniform::set((name + "." + UNIFORMS::GRB::point_location).c_str(), location, program);
    PROGRAM::Uniform::set((name + "." + UNIFORMS::GRB::point_radius).c_str(), radius, program);
    PROGRAM::Uniform::set_int((name + "." + UNIFORMS::GRB::point_factor).c_str(), factor, program);
}