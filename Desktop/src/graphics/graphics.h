//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_GRAPHICS_H
#define ASCENSION_GRAPHICS_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

namespace ASC {
    namespace GRAPHICS {

        extern std::map<std::string, unsigned> resources;

        namespace GL {
            extern GLFWwindow *window;

            void init(unsigned width, unsigned height, const char *title, unsigned vsync = 0);
        }

        namespace PROGRAM {
            extern unsigned active;

            inline void use(unsigned id) {
                glUseProgram(active = id);
            }

            unsigned create(const char *vertex, const char *fragment, const char *geometry = nullptr);

            class Uniform {
            public:
                // subclass-based uniform setter
                virtual void set(std::string name, unsigned program = active) const = 0;

                // bool
                static void set_bool(const char *name, bool value, unsigned program = active);

                // int
                static void set_int(const char *name, int value, unsigned program = active);

                // float
                static void set(const char *name, float value, unsigned program = active);

                // {float, float}
                static void set(const char *name, const glm::vec2 &value, unsigned program = active);

                // {float, float, float}
                static void set(const char *name, const glm::vec3 &value, unsigned program = active);

                // {float, float, float, float}
                static void set(const char *name, const glm::vec4 &value, unsigned program = active);

                // 2x2
                static void set(const char *name, const glm::mat2 &mat, unsigned program = active);

                // 3x3
                static void set(const char *name, const glm::mat3 &mat, unsigned program = active);

                // 4x4
                static void set(const char *name, const glm::mat4 &mat, unsigned program = active);

                // set array
                template<typename T>
                static void set_array(const std::string &name, unsigned count, const T *elements,
                                      unsigned program = active) {
                    static_assert(std::is_base_of<Uniform, T>::value, "T is not a subclass of Uniform");
                    auto el = (T *) elements;
                    for (unsigned i = 0; i < count; i++) {
                        el[i].set(name + "[" + std::to_string(i) + "]", program);
                    }
                }
            };
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

            void set(unsigned program = PROGRAM::active);
        } matrices;
    }
}

#endif //ASCENSION_GRAPHICS_H
