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

NAMESPACE(ASC, GRAPHICS)
        extern std::map<std::string, unsigned> resources;

        namespace GL {
            extern GLFWwindow *window;

            void init(unsigned width, unsigned height, CString title, unsigned vsync = 0);
        }


        namespace PROGRAM {
            extern unsigned active;

            // bool
            void set_bool(CString name, bool value, unsigned int program = active);

            // int
            void set_int(CString name, int value, unsigned int program = active);

            // float
            void set(CString name, float value, unsigned int program = active);

            // {float, float}
            void set(CString name, const glm::vec2 &value, unsigned int program = active);

            // {float, float, float}
            void set(CString name, const glm::vec3 &value, unsigned int program = active);

            // {float, float, float, float}
            void set(CString name, const glm::vec4 &value, unsigned int program = active);

            // 2x2
            void set(CString name, const glm::mat2 &mat, unsigned int program = active);

            // 3x3
            void set(CString name, const glm::mat3 &mat, unsigned int program = active);

            // 4x4
            void set(CString name, const glm::mat4 &mat, unsigned int program = active);

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
                double x, y;
            } cursor;

            struct {
                // time since loop start
                double elapsed;

                // time between current nad previous frame
                double delta;
            };

            static void update();
        } globals;

        extern struct Matrices {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 projection;

            void set(unsigned prog = PROGRAM::active);
        } matrices;
N2

#endif //ASCENSION_GRAPHICS_H
