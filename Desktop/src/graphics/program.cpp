//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#include <GL/glew.h>
#include <graphics/graphics.h>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>

using namespace ASC::GRAPHICS;
unsigned PROGRAM::active{0};

static int infoLogLength;

enum Shaders {
    vertex = GL_VERTEX_SHADER,
    geometry = GL_GEOMETRY_SHADER,
    fragment = GL_FRAGMENT_SHADER
};

// bool
void PROGRAM::Uniform::set_bool(const char *name, bool value, unsigned int program) {
    glUniform1i(glGetUniformLocation(program, name), (int) value);
}

// int
void PROGRAM::Uniform::set_int(const char *name, int value, unsigned int program) {
    glUniform1i(glGetUniformLocation(program, name), value);
}

// float
void PROGRAM::Uniform::set(const char *name, float value, unsigned int program) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

// {float, float}
void PROGRAM::Uniform::set(const char *name, const glm::vec2 &value, unsigned int program) {
    glUniform2fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// {float, float, float}
void PROGRAM::Uniform::set(const char *name, const glm::vec3 &value, unsigned int program) {
    glUniform3fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// {float, float, float, float}
void PROGRAM::Uniform::set(const char *name, const glm::vec4 &value, unsigned int program) {
    glUniform4fv(glGetUniformLocation(program, name), 1, &value[0]);
}

// 2x2
void PROGRAM::Uniform::set(const char *name, const glm::mat2 &mat, unsigned int program) {
    glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE, &mat[0][0]);
}

// 3x3
void PROGRAM::Uniform::set(const char *name, const glm::mat3 &mat, unsigned int program) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, &mat[0][0]);
}

// 4x4
void PROGRAM::Uniform::set(const char *name, const glm::mat4 &mat, unsigned int program) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &mat[0][0]);
}

static unsigned createShader(Shaders type, const char *filePath) {
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
    const char *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, nullptr);
    glCompileShader(shaderID);

    // Check for errors
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> shaderErrorMessage((unsigned) infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }

    return shaderID;
}

unsigned ASC::GRAPHICS::PROGRAM::create(const char *vertex, const char *fragment, const char *geometry) {
    infoLogLength = 0;

    const unsigned shaders[3] = {
            createShader(Shaders::vertex, vertex),
            createShader(Shaders::geometry, geometry),
            createShader(Shaders::fragment, fragment)
    };

    if (!(shaders[0] | shaders[1] | shaders[2])) {
        printf("Couldn't create program\n");
        return 0;
    }

    // Link program
    unsigned programID = glCreateProgram();

    for (unsigned shader: shaders) {
        if (shader != 0)
            glAttachShader(programID, shader);
    }

    glLinkProgram(programID);

    // Check program
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> ProgramErrorMessage((unsigned) infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    // Cleanup
    for (unsigned shader: shaders) {
        if (shader != 0) {
            glDetachShader(programID, shader);
            glDeleteShader(shader);
        }
    }

    return programID;
}
