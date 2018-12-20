//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#ifndef ASCENSION_MODULES_H
#define ASCENSION_MODULES_H

#include <graphics/scenes/SceneBase.h>
#include "code_organizers.h"
#include "graphics/Framebuffer/Framebuffer.h"

NAMESPACE(ASC, GRAPHICS, SCENES)
            class Modules : public SceneBase {
                const ASC::GRAPHICS::Framebuffer fbo{0.f};

            SCENE_BASE(Modules)

                void fade_in();
                void fade_out();
            };
N3

#endif //ASCENSION_MODULES_H
