//
// Created by Vladyslav Yazykov on 11/09/2018.
//

#ifndef ASCENSION_DYNAMICSCENEAPI_H
#define ASCENSION_DYNAMICSCENEAPI_H

#include "string"
#include "scenes/Base/Base.h"
#include <unordered_map>

typedef std::unordered_map<std::string, ASC::GRAPHICS::SCENES::Base *(*)()> scene_map;

extern struct AscmlApi {
    std::unordered_map<std::string, ASC::GRAPHICS::SCENES::Base *(*)()> scenes;
    unsigned *program;
} api;

#endif //ASCENSION_DYNAMICSCENEAPI_H
