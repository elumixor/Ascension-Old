//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#include "elements.h"

ASC::GRAPHICS::RESOURCES::Container::~Container() {
    for (auto el : objects)
        delete (el.second);
    for (auto el: vaos) {
        el.second->free();
        delete el.second;
    }
}

ASC::GRAPHICS::RESOURCES::VAO *
ASC::GRAPHICS::RESOURCES::Container::get_vao(const String &name, std::initializer_list<unsigned int> components) {
    auto instance = container();

    auto result = instance->vaos[name];

    if (!result) instance->vaos[name] = new VAO(name.c_str(), components);
    return instance->vaos[name];
}

unsigned ASC::GRAPHICS::RESOURCES::Container::get_program(const String &name) {
    auto instance = container();

    if (instance->programs.find(name) == instance->programs.end()) {
        instance->programs[name] = ASC::GRAPHICS::PROGRAM::create(name);
    }

    return instance->programs[name];
}

ASC::GRAPHICS::RESOURCES::Container *ASC::GRAPHICS::RESOURCES::Container::container() {
    static Container instance;
    return &instance;
}
