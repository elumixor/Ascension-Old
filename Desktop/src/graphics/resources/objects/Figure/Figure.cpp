//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#include "Figure.h"
#include "graphics/graphics.h"

void ASC::GRAPHICS::RESOURCES::Figure::render(const std::string &base_name) const {
    glm::mat4 _model{model};

    model = glm::translate(glm::mat4{1.f}, position) * model;
    UNI_FIELD(model);
    model = _model;
    vao->render();
}
