//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#include "Figure.h"
#include "graphics/graphics.h"

void ASC::GRAPHICS::RESOURCES::Figure::render(const std::string &base_name) const {
    UNI_FIELD(model);
    vao->render();
}
