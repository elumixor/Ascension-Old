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

    matrices.projection = glm::perspective(glm::radians(PARAMS::persepctive_zoom),
                                           (float) width / (float) height, 0.1f, 100.0f);
}

void GL::init(unsigned width, unsigned height, const char *title, unsigned int vsync) {
    glewExperimental = GL_TRUE;

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        exit(-1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, PARAMS::gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, PARAMS::gl_version_minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        glfwTerminate();
        exit(-1);
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

#ifdef ASCENSION_DEBUG
#ifdef ASCENSION_WINDOWS
    printf("Debug output enabled\n");
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    printf("%x", &openglCallbackFunction);
    printf("%x", openglCallbackFunction);
    glDebugMessageCallback(openglCallbackFunction, nullptr);
#endif
#endif

    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSwapInterval(vsync);
}