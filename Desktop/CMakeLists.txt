cmake_minimum_required(VERSION 3.0)
project(Ascension)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(OpenGL REQUIRED)

# Compile external dependencies
add_subdirectory(external)

set(GL_INCLUDES
        ${CMAKE_CURRENT_LIST_DIR}/external/glfw/include
        ${CMAKE_CURRENT_LIST_DIR}/external/glm
        ${CMAKE_CURRENT_LIST_DIR}/external/glew/include
        )
include_directories(
        ${GL_INCLUDES}
        src)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        glew
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

# Source files
set(src src/main.cpp
        src/code_organizers.h

        src/constants/constants.cpp src/constants/constants.h

        src/graphics/graphics.h src/graphics/graphics.cpp
        src/graphics/gl.cpp
        src/graphics/program.cpp

        src/graphics/Mainframe/Mainframe.cpp src/graphics/Mainframe/Mainframe.h

        src/graphics/scenes/SceneBase.h
        src/graphics/scenes/Home/Home.cpp src/graphics/scenes/Home/Home.h

        src/graphics/resources/elements.h src/graphics/resources/elements.cpp
        src/graphics/resources/VAO/VAO.cpp src/graphics/resources/VAO/VAO.h
        src/graphics/resources/objects/Base.h src/graphics/resources/objects/Base.h
        src/graphics/resources/objects/Point/Point.h src/graphics/resources/objects/Point/Point.cpp
        src/graphics/resources/objects/GradientBackgorund/GradientBackground.cpp src/graphics/resources/objects/GradientBackgorund/GradientBackground.h
        src/graphics/resources/objects/Figure/Figure.cpp src/graphics/resources/objects/Figure/Figure.h
        src/graphics/scenes/overlays/Modules.cpp src/graphics/scenes/overlays/Modules.h
        src/graphics/scenes/keys/keys.h src/graphics/scenes/keys/keys.cpp
        src/util/Singleton.h
        src/graphics/Framebuffer/Framebuffer.cpp src/graphics/Framebuffer/Framebuffer.h src/graphics/animation/animation.h src/graphics/animation/animation.cpp src/util/list.h src/util/FString.h src/util/FString.cpp src/util/literals.h
        src/util/map.h src/util/linked_map.h src/util/proxy.h src/util/Bezier.h src/util/math.h)

if ("${CMAKE_CURRENT_LIST_DIR}/meshes" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_DIR}/meshes/generated")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_LIST_DIR}/meshes/generated")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/meshes/generated")
    execute_process(COMMAND python "${CMAKE_CURRENT_LIST_DIR}/meshes/transform.py")
endif ()

# exe
add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})