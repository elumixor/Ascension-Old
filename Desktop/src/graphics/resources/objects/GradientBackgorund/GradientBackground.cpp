//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#include "GradientBackground.h"
#include <graphics/graphics.h>

void ASC::GRAPHICS::RESOURCES::GradientBackground::render(const std::string &base_name) const {
    UNI_INT(points_count);
    UNI_ARRAY(points, points_count);
    vao->render();
}
