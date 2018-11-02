project(ASCML)
include_directories(${GL_INCLUDES})

# Objects

file(REMOVE_RECURSE "${CMAKE_CURRENT_LIST_DIR}/objects/generated")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/objects/generated")

execute_process(COMMAND python ${CMAKE_CURRENT_LIST_DIR}/py/objects.parser.py)
execute_process(COMMAND python ${CMAKE_CURRENT_LIST_DIR}/py/cmake.py)

add_subdirectory(objects/generated)
include_directories(objects/generated)

# Scenes
include_directories(.
        scenes
        objects)

add_library(${PROJECT_NAME} SHARED
        scenes/generated/TestScene/DynamicScene.cpp scenes/generated/TestScene/DynamicScene.h)
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS} Objects)