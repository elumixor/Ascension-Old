//
// Created by Vladyslav Yazykov on 04/12/2018.
//

#include "animation.h"
#include "string"

using namespace ASC::GRAPHICS;


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

//Animation &Animation::operator=(const Animation *other) {

//    return *this;
//}

Animations ASC::GRAPHICS::animations{};
Animable::Animable(Animable &&other) noexcept : _modify{other._modify}, _free{other._free}, _data{other._data},
                                                _diff{other._diff} {
    other._data = other._diff = nullptr;
}
Animable::Animable(void *data, void *_diff, Animable::Modify modify, Animable::Free _free) : _modify{modify},
                                                                                             _free{_free}, _data{data},
                                                                                             _diff{_diff} {}
ani::Sustained::Sustained(Animable animable, unsigned steps, Easing easing) :
        steps{steps}, animable{std::move(animable)}, easing{easing} {}
bool ani::Sustained::step() const {
    if (current == steps)
        return false;

    current++;
    animable.modify(easing((float) current / steps));

    return true;
}
