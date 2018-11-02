project(Objects)
include_directories(.)
add_library(${PROJECT_NAME} STATIC ../ObjectBase.h
	../../AscmlApi.h../../AscmlApi.cpp
	../../scenes/Base/Base.h ../../scenes/Base/Base.cpp
)
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
