//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_ELEMENTS_H
#define ASCENSION_ELEMENTS_H

#include <code_organizers.h>
#include <string>
#include <unordered_map>
#include <graphics/resources/VAO/VAO.h>
#include "graphics/graphics.h"
#include "objects/Base.h"

#define GET_ELEMENT(type, name) ASC::GRAPHICS::RESOURCES::Container::get_element<ASC::GRAPHICS::RESOURCES::type>(name)
#define GET_PROGRAM(name) ASC::GRAPHICS::RESOURCES::Container::get_program(name)
#define GET_VAO ASC::GRAPHICS::RESOURCES::Container::get_vao

#define SINGLE_DRAW_CALL GET_VAO("__SDC__")

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            class Container {
                std::unordered_map<String, Base *> objects;
                std::unordered_map<String, unsigned> programs;
                std::unordered_map<String, VAO*> vaos;

                Container() = default;

                static Container *container();

            public:
                template<typename T>
                static T *get_element(const String &name) {
                    static_assert(std::is_base_of<Base, T>::value,
                                  "GET_ELEMENT(type, name): type should derive from ELEMENTS::Base");

                    auto instance = container();
                    auto result = instance->objects[name];

                    if (!result) instance->objects[name] = new(T);
                    return (T *) instance->objects[name];
                }

                static unsigned get_program(const String &name);

                static VAO* get_vao(const String &name, std::initializer_list<unsigned> components = {});

                ~Container();
            };
N3
#endif //ASCENSION_ELEMENTS_Hслишком высокого мнения обо мне, вот

