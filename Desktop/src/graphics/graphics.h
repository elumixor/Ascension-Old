//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_GRAPHICS_H
#define ASCENSION_GRAPHICS_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <graphics/resources/objects/Base.h>
#include "code_organizers.h"

#define _set_func_impl(fname, type) void fname(CString name, type value, unsigned int program)
#define _set_func(fname, type) void fname(CString name, type value, unsigned int program = active)
#define __set_func_impl(type) _set_func_impl(PROGRAM::set, type)
#define __set_func(type) _set_func(set, type)

NAMESPACE(ASC, GRAPHICS)
        class Mainframe;

        extern std::map<std::string, unsigned> resources;

        namespace GL {
            extern GLFWwindow *window;

            void init(unsigned width, unsigned height, CString title, unsigned vsync = 0);
        }


        namespace PROGRAM {
            extern unsigned active;

            _set_func(set_bool, bool);

            _set_func(set_int, int);

            __set_func(float);

            __set_func(const glm::vec2 &);

            __set_func(const glm::vec3 &);

            __set_func(const glm::vec4 &);

            __set_func(const glm::mat2 &);

            __set_func(const glm::mat3 &);

            __set_func(const glm::mat4 &);

            // set array
            template<typename T>
            static void set_array(const std::string &name, unsigned count, const T *elements) {
                static_assert(std::is_base_of<RESOURCES::Base, T>::value, "T is not a subclass of Base");
                auto el = (T *) elements;
                for (unsigned i = 0; i < count; i++) {
                    el[i].render(name + "[" + std::to_string(i) + "]");
                }
            }

            unsigned create(CString vertex, CString fragment, CString geometry);

            unsigned create(const String &name);
        }

        extern struct Globals {
            struct {
                double x, y; // double for compatibility with OpenGL
            } cursor;

            struct {
                double elapsed, delta; // // double for compatibility with OpenGL
            };

            struct Matrices {
                glm::mat4 view;
                glm::mat4 projection;

                void set();
            } matrices;

            struct {
                unsigned width;
                unsigned height;
            } screen;

            Mainframe *mainframe;

            static void update();
        } globals;

N2

#endif //ASCENSION_GRAPHICS_H
