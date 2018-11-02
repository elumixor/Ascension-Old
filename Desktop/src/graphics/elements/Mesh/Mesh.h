//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#ifndef ASCENSION_VERTEXOBJECT_H
#define ASCENSION_VERTEXOBJECT_H

#include <GL/glew.h>

namespace ASC {
    namespace GRAPHICS {
        namespace ELEMENTS {
            class Mesh {
            public:
                struct VertexAttribute {
                    // actual attribute data (e.g. positions)
                    void *data;

                    // data byte size
                    size_t size;

                    // type of data (e.g. GL_FLOAT)
                    GLenum type;

                    // number of components in attribute per vertex (e.g. 3 for position {x, y, z})
                    unsigned components_count;
                };

                static const unsigned char LOCATION{0b00000001};
                static const unsigned char TEXTURE{0b00000010};
                static const unsigned char NORMAL{0b00000100};
                static const unsigned char COLOR{0b00001000};
            private:
                mutable unsigned VAO{0}, VBO{0}, IBO{0};
                unsigned indices_count{0};
                size_t VBO_size{0};
                const unsigned char attributes;
            public:
                Mesh(unsigned indices_count, const unsigned *indices,
                     unsigned attributes_count, const VertexAttribute *attributes);

                explicit Mesh(const char *ascobj_path = "", unsigned char attributes = 0b00000000);

                /// copy
                Mesh(const Mesh &other);

                /// move
                Mesh(Mesh &&other) noexcept;

                Mesh &operator=(const Mesh &other);

                virtual ~Mesh() {
                    glDeleteBuffers(1, &VBO);
                    glDeleteBuffers(1, &IBO);
                    glDeleteVertexArrays(1, &VAO);
                }

                void render() const;
            };
        }
    }
}


#endif //ASCENSION_VERTEXOBJECT_H
