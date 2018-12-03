//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#include <GL/glew.h>
#include <graphics/Framebuffer/Framebuffer.h>
#include "Modules.h"
#include "util/util.h"
#include "graphics/graphics.h"

ASC::GRAPHICS::SCENES::Modules::Modules() {

}

void ASC::GRAPHICS::SCENES::Modules::render() {
    LOG("displaying overlay");
    fbo.write();


    glClearColor(0.0f, 0.f, 0.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);
    fbo.opacity = .8f;
    fbo.render();
}
