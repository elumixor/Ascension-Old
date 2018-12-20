//
// Created by Vladyslav Yazykov on 28/11/2018.
//

#include "keys.h"

bool ASC::GRAPHICS::KEYS::Key::release() const {
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

bool ASC::GRAPHICS::KEYS::Key::press() const{
    if (condition()) {
        condition();
        if (!pressed) {
            pressed = true;
            return true;
        }
    } else {
        pressed = false;
    }

    return false;
}
