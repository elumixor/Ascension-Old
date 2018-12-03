//
// Created by Vladyslav Yazykov on 28/11/2018.
//

#include "keys.h"

bool ASC::GRAPHICS::KEYS::release(Predicate condition) {
    static bool pressed{false};

    if (condition()) {
        pressed = true;
    } else {
        if (pressed) {
            pressed = false;
            return true;
        }
    }

    return false;
}

bool ASC::GRAPHICS::KEYS::press(Predicate condition) {

    static bool pressed{false};

    if (condition()) {
        if (!pressed) {
            pressed = true;
            return true;
        }
    } else {
        pressed = false;
    }

    return false;
}
