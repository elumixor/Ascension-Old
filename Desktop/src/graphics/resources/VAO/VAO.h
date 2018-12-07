//
// Created by Vladyslav Yazykov on 17/11/2018.
//

#ifndef ASCENSION_VAO_H
#define ASCENSION_VAO_H

#include <GL/glew.h>
#import "code_organizers.h"
#import "string"
#import "vector"
#include <constants/constants.h>

NAMESPACE(ASC, GRAPHICS, RESOURCES)
            class VAO {
            private:
                unsigned vao{0}, vbo{0}, ibo{0};
                unsigned indices_count{0};
                bool has_components{true};
            public:
                /**
                 * Specify draw mode (e.g. GL_POINTS, GL_TRIANGLES)
                 */
                GLenum draw_mode;

                /**
                 * Create VAO, load into OpenGL
                 * @param name Name of object (will be used creating relative path)
                 * @param layout Template parameters specify vertex layout.
                 * E.g.: '3, 2, 3' specifies a vertex, that consists of 3 vertex attributes:
                 * 3 floats, 2 floats and 3 floats.
                 * @param draw_mode GL draw mode (e.g. GL_TRIANGLES, GL_POINTS)
                 */
                explicit VAO(CString name, std::initializer_list<unsigned> components = {},
                             GLenum draw_mode = GL_TRIANGLES);

                /**
                 * GL render call
                 */
                void render() const;

                virtual void free();
            };
N3


#endif //ASCENSION_VAO_H
