//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#define ASCENSION_DEBUG

#include <cstdio>
#include <GL/glew.h>
#include <cstdlib>
#include <constants/constants.h>
#include <glm/gtc/matrix_transform.hpp>
#include "graphics.h"
#include "util/util.h"

using namespace ASC::GRAPHICS;
using namespace ASC::CONSTANTS;

GLFWwindow *GL::window{nullptr};

#ifdef ASCENSION_DEBUG
#ifdef ASCENSION_WINDOWS

static void APIENTRY openglCallbackFunction(GLenum, GLenum, GLuint, GLenum severity, GLsizei,
                                            const GLchar *message, const void *) {
    printf("%s\n", message);
    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        exit(-1);
    }
}

#endif
#endif

static void resizeCallback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
    globals.screen = {(unsigned) width, (unsigned) height};

    globals.matrices.projection = glm::perspective(glm::radians(PARAMS::persepctive_zoom),
                                                   (float) width / (float) height, 0.1f, 100.0f);
}

void GL::init(unsigned width, unsigned height, CString title, unsigned int vsync) {
    glewExperimental = GL_TRUE;

    require(glfwInit(), "Failed to initialize GLFW");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, PARAMS::gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, PARAMS::gl_version_minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    require (window, "Failed to open GLFW window");

    glfwMakeContextCurrent(window);

    require(glewInit() == GLEW_OK, "Failed to initialize GLEW");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSwapInterval(vsync);

    globals.screen = {width, height};
}