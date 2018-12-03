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
                const ASC::GRAPHICS::Framebuffer fbo{};
                float opacity {0.5f};

            SCENE_BASE(Modules)

            };
N3

#endif //ASCENSION_MODULES_H
