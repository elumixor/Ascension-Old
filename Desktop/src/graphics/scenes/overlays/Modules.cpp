//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#include <GL/glew.h>
#include <graphics/Framebuffer/Framebuffer.h>
#include <graphics/animation/animation.h>
#include <graphics/Mainframe/Mainframe.h>
#include "Modules.h"
#include "graphics/graphics.h"

ASC::GRAPHICS::SCENES::Modules::Modules() = default;

void ASC::GRAPHICS::SCENES::Modules::render() {
    fbo.write();


    glClearColor(0.0f, 0.f, 0.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);
//    fbo.opacity = .0f;
    fbo.render();
}
void ASC::GRAPHICS::SCENES::Modules::fade_in() {
    ASC::GRAPHICS::globals.mainframe->overlay = this;
    animations.fleeting("opacity", &fbo.opacity, 0.8f, .3f);
}

void ASC::GRAPHICS::SCENES::Modules::fade_out() {
    animations.reverse("opacity");
    // and then...
    if (!animations.is_present("opacity"))
        ASC::GRAPHICS::globals.mainframe->overlay = nullptr;
}
