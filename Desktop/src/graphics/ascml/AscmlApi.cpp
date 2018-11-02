//
// Created by Vladyslav Yazykov on 11/09/2018.
//


#include <graphics/ascml/scenes/generated/TestScene/DynamicScene.h>
#include "AscmlApi.h"

ASC::GRAPHICS::SCENES::Base *newScene() {
    return DynamicScene::instance();
}

AscmlApi api{{{"DynamicScene", newScene}}, nullptr};
