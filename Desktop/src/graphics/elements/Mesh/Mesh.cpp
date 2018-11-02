//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#include <cstring>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <constants/constants.h>
#include "Mesh.h"

ASC::GRAPHICS::ELEMENTS::Mesh::Mesh(const unsigned indices_count, const unsigned *indices,
                                    const unsigned attributes_count, const VertexAttribute *attributes)
        : indices_count{indices_count}, attributes{0b00000000} {

    // generate vao/buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // bind VAO
    glBindVertexArray(VAO);

    // count total size
    for (unsigned i = 0; i < attributes_count; i++) {
        VBO_size += attributes[i].size;
    }

    size_t offset{0};

    // allocate space
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, VBO_size, nullptr, GL_STATIC_DRAW);

    for (unsigned i = 0; i < attributes_count; i++) {
        // copy data into buffer
        glBufferSubData(GL_ARRAY_BUFFER, offset, attributes[i].size, attributes[i].data);
        glVertexAttribPointer(i, attributes[i].components_count, attributes[i].type, GL_FALSE, 0, (void *) offset);
        glEnableVertexAttribArray(i);

        offset += attributes[i].size;
    }

    // pass indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(unsigned), indices, GL_STATIC_DRAW);

    // NOTE: I MIGHT NEED TO RE-ARRANGE BUFFER DATA INPUT (e.g. VBO first, IBO second, VAO pointers last)

    glBindVertexArray(0);
}

ASC::GRAPHICS::ELEMENTS::Mesh::Mesh(const ASC::GRAPHICS::ELEMENTS::Mesh &other) :
        VBO_size{other.VBO_size}, indices_count{other.indices_count}, attributes{other.attributes} {
    // todo..?
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_COPY_READ_BUFFER, other.VBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBO_size);

    glBindBuffer(GL_COPY_READ_BUFFER, other.IBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(unsigned), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_COPY_WRITE_BUFFER, IBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(unsigned) * indices_count);
}

ASC::GRAPHICS::ELEMENTS::Mesh &
ASC::GRAPHICS::ELEMENTS::Mesh::operator=(const ASC::GRAPHICS::ELEMENTS::Mesh &other) {
    VBO_size = other.VBO_size;
    indices_count = other.indices_count;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_COPY_READ_BUFFER, other.VBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBO_size);

    glBindBuffer(GL_COPY_READ_BUFFER, other.IBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, IBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(unsigned) * indices_count);

    return *this;
}

ASC::GRAPHICS::ELEMENTS::Mesh::Mesh(ASC::GRAPHICS::ELEMENTS::Mesh &&other) noexcept :
        VBO_size{other.VBO_size}, indices_count{other.indices_count}, VAO{other.VAO}, VBO{other.VBO}, IBO{other.IBO},
        attributes{other.attributes} {

    other.VBO_size = other.indices_count = other.VAO = other.VBO = other.IBO = 0;
}

ASC::GRAPHICS::ELEMENTS::Mesh::Mesh(const char *ascobj_path, unsigned char attributes) : attributes{attributes} {
    // generate vao/buffers
    glGenVertexArrays(1, &VAO);

    if (!attributes) return;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // bind VAO
    glBindVertexArray(VAO);

    // open file with data
    FILE *fp{fopen(ascobj_path, "rb")};
    if (!fp) {
        printf("Couldn't open file: %s\n", ascobj_path);
        exit(ASC::CONSTANTS::ERRORS::file_open);
    }

    unsigned vertex_count;
    fread(&vertex_count, sizeof(unsigned), 1, fp);
    fread(&indices_count, sizeof(unsigned), 1, fp);

    // allocate space
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, VBO_size = vertex_count * 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // buffer data writing offset
    size_t offset{0};

    // location
    if (attributes & Mesh::LOCATION) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
        glEnableVertexAttribArray(0);
        fread(ptr, offset += 3 * sizeof(float) * vertex_count, 1, fp);
    }

    // texture
    if (attributes & Mesh::TEXTURE) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) offset);
        glEnableVertexAttribArray(1);
        size_t size{2 * sizeof(float) * vertex_count};
        fread((char *) ptr + offset, size, 1, fp);
        offset += size;
    }

    // normals
    if (attributes & Mesh::NORMAL) {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) offset);
        glEnableVertexAttribArray(2);
        fread((char *) ptr + offset, 3 * sizeof(float) * vertex_count, 1, fp);
    }

    // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(unsigned), nullptr, GL_STATIC_DRAW);
    ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    fread(ptr, indices_count * sizeof(unsigned), 1, fp);

    // cleanup
    fclose(fp);
    glBindVertexArray(0);
}

void ASC::GRAPHICS::ELEMENTS::Mesh::render() const {
    glBindVertexArray(VAO);
    if (!attributes) {
        glDrawArrays(GL_POINTS, 0, 1);
    } else {
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
    }
}
