//
// Created by Vladyslav Yazykov on 17/11/2018.
//

#include "VAO.h"
#include "util/FString.h"

ASC::GRAPHICS::RESOURCES::VAO::VAO(const char *name, std::initializer_list<unsigned int> components, GLenum draw_mode)
        : draw_mode{draw_mode} {
    // Get components count and compute vertex size
    unsigned vertex_size{0};
    for (auto c: components) vertex_size += c;
    has_components = vertex_size != 0;

    // Generate VAO
    glGenVertexArrays(1, &vao);

    if (!has_components) return;

    // Generate buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    // Bind VAO
    glBindVertexArray(vao);

    // Open .ascobj file
    String file_path = (FString(ASC::CONSTANTS::PATHS::MESHES::base) % name).c_str();
    FILE *fp{fopen(file_path.c_str(), "rb")};
    require(fp, "Could not open mesh file: '%s'"_fs % file_path);

    // Get .ascobj layout
    unsigned vertex_count;
    fread(&vertex_count, sizeof(unsigned), 1, fp);
    fread(&indices_count, sizeof(unsigned), 1, fp);

    // allocate space
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size * sizeof(float), nullptr, GL_STATIC_DRAW);
    auto ptr = (char *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // buffer data writing offset
    size_t offset{0};
    unsigned vertex_attrib_index{0};

    // Read data directly into GL buffer
    for (auto component_parts: components) {
        glVertexAttribPointer(vertex_attrib_index, component_parts,
                              GL_FLOAT, GL_FALSE, 0, (void *) offset);
        glEnableVertexAttribArray(vertex_attrib_index);

        vertex_attrib_index++;

        ptr += offset;
        offset += component_parts * sizeof(float) * vertex_count;

        fread(ptr, component_parts * vertex_count * sizeof(float), 1, fp);
    }

    // Read indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(unsigned), nullptr, GL_STATIC_DRAW);
    ptr = (char *) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    fread(ptr, indices_count * sizeof(unsigned), 1, fp);

    // cleanup
    fclose(fp);
    glBindVertexArray(0);

    LOG("VAO for %s successfully created"_fs % name);
}

void ASC::GRAPHICS::RESOURCES::VAO::render() const {
    glBindVertexArray(vao);

    if (has_components) // Regular draw
        glDrawElements(draw_mode, indices_count, GL_UNSIGNED_INT, nullptr);
    else // Dummy draw call
        glDrawArrays(GL_POINTS, 0, 1);
}

void ASC::GRAPHICS::RESOURCES::VAO::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);
}
