//
// Created by Vladyslav Yazykov on 04/12/2018.
//

#include "animation.h"
#include "string"

using namespace ASC::GRAPHICS;

Animation *ASC::GRAPHICS::animations{nullptr};
Animation *ASC::GRAPHICS::end_animations{nullptr};

void ASC::GRAPHICS::free_animations(){
    LOG("freeing");
    Animation *animation = animations;
    while (animation) {
        auto next = animation->next();
        delete animation;
        animation = next;
    }
}

//void ASC::GRAPHICS::no_step(void *, float) {}

float Easings::linear(float) {
    return 1.f;
}

//void Animation::stop() {

//}

//void Animation::reverse() {
//
//}

//void Animation::step() {
//    if (current >= steps) stop();
//    current++;
//    float percent = (float) current / steps;
//    _step(data, easing(percent));
//}

Animation &Animation::operator=(const Animation *other) {

    return *this;
}