project(TestScene)

include_directories(../objects)

add_library(${PROJECT_NAME} SHARED TestScene/DynamicScene.cpp TestScene/DynamicScene.h TestScene/DynamicSceneApi.h TestScene/DynamicSceneApi.cpp)
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS} Objects)