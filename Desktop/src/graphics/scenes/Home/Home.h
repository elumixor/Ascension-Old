//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_HOME_H
#define ASCENSION_HOME_H

#include <graphics/scenes/SceneBase.h>
#include <code_organizers.h>
#include <graphics/resources/objects/GradientBackgorund/GradientBackground.h>
#include <graphics/resources/objects/Figure/Figure.h>
#include <util/Singleton.h>

NAMESPACE(ASC, GRAPHICS, SCENES)
            class Home : public SceneBase {
                SCENE_BASE(Home)
                RESOURCES::GradientBackground *background{nullptr};
                RESOURCES::Figure *figure{nullptr};
                unsigned bg_shader{0};
                unsigned fg_shader{0};
            };
N3

#endif //ASCENSION_HOME_H
