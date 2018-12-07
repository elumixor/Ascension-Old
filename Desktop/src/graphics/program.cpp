//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#include <GL/glew.h>
#include <graphics/graphics.h>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <constants/constants.h>
#include "graphics.h"
#include "util/FString.h"

using namespace ASC::GRAPHICS;

unsigned PROGRAM::active{0};

static int infoLogLength;

enum Shaders {
    vertex = GL_VERTEX_SHADER,
    geometry = GL_GEOMETRY_SHADER,
    fragment = GL_FRAGMENT_SHADER
};


_set_func_impl(PROGRAM::set_bool, bool) {
    glUniform1i(glGetUniformLocation(program, name), (int) value);
}

_set_func_impl(PROGRAM::set_int, int) {
    glUniform1i(glGetUniformLocation(program, name), value);
}

// float
__set_func_impl(float) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

// {float, float}
__set_func_impl(const glm::vec2 &) {
    glUniform2fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// {float, float, float}
__set_func_impl(const glm::vec3 &) {
    glUniform3fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// {float, float, float, float}
__set_func_impl(const glm::vec4 &) {
    glUniform4fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// 2x2
__set_func_impl(const glm::mat2 &) {
    glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

// 3x3
__set_func_impl(const glm::mat3 &) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

// 4x4
__set_func_impl(const glm::mat4 &) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

static unsigned createShader(Shaders type, CString filePath) {
    if (!filePath) return 0;

    // Create shader
    unsigned shaderID = glCreateShader(type);

    // Read shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(filePath, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream stringStream;
        stringStream << shaderStream.rdbuf();
        shaderCode = stringStream.str();
        shaderStream.close();
    } else {
        printf("Couldn't open shader file: %s.\n", filePath);
        exit(-1);
    }

    //  Compile shader
    CString sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, nullptr);
    glCompileShader(shaderID);

    // Check for errors
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> shaderErrorMessage((unsigned) infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &shaderErrorMessage[0]);
        LOG("Error compiling shader: %s"_fs % &shaderErrorMessage[0]);
    }

    return shaderID;
}

unsigned PROGRAM::create(CString vertex, CString fragment, CString geometry) {
    infoLogLength = 0;

    const unsigned shaders[3] = {
            createShader(Shaders::vertex, vertex),
            createShader(Shaders::geometry, geometry),
            createShader(Shaders::fragment, fragment)
    };

    require((shaders[0] | shaders[1] | shaders[2]), "Couldn't create program");

    // Link program
    unsigned programID = glCreateProgram();

    for (unsigned shader: shaders)
        if (shader != 0)
            glAttachShader(programID, shader);

    glLinkProgram(programID);

    // Check program
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> ProgramErrorMessage((unsigned) infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, &ProgramErrorMessage[0]);
        LOG("Error linking program: %s"_fs % &ProgramErrorMessage[0]);
    }

    // Cleanup
    for (unsigned shader: shaders)
        if (shader != 0) {
            glDetachShader(programID, shader);
            glDeleteShader(shader);
        }

    return programID;
}

unsigned PROGRAM::create(const String &name) {
    const auto &paths = ASC::CONSTANTS::PATHS::program;
    String vertex = format_str(paths.vertex, name);
    String fragment = format_str(paths.fragment, name);
    String geometry = format_str(paths.geometry, name);

    return PROGRAM::create(vertex.c_str(),
                           fragment.c_str(),
                           std::ifstream(geometry) ? geometry.c_str() : nullptr);
}
